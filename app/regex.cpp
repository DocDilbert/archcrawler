#include "regex.h"

#include <stdio.h>

#include <cstring>
#include <memory>

#define PCRE2_CODE_UNIT_WIDTH 8
#include "app_config.h"
#include "pcre2.h"

struct Regex::impl {
  pcre2_code* re = nullptr;
  pcre2_match_data* match_data = nullptr;
};

class MatchIter : public IMatchIter {
 public:
  MatchIter(pcre2_match_data* match_data, int no_of_matches) : match_data_(match_data), no_of_matches_(no_of_matches) {
    idx_ = 0;
    if (no_of_matches_ != 0) {
      ovector_ = pcre2_get_ovector_pointer(match_data_);
    }
  }
  virtual ~MatchIter() {}
  bool IsDone() override {
    if (idx_ >= no_of_matches_) {
      return true;
    }
    return false;
  }
  void Next() override { idx_++; }

  Match Current() override {
    Match rmatch;
    rmatch.begin_pos = ovector_[idx_ * 2];
    rmatch.end_pos = ovector_[idx_ * 2 + 1];
    rmatch.length = rmatch.end_pos - rmatch.begin_pos;

    return rmatch;
  }

 private:
  pcre2_match_data* match_data_ = nullptr;
  PCRE2_SIZE* ovector_ = nullptr;
  int no_of_matches_ = 0;
  int idx_ = 0;
};

Regex::Regex(std::string pattern) : pimpl_(new Regex::impl()) {
  logger_ = spdlog::get(app_logger_name);

  int errornumber;
  int rc;

  PCRE2_SIZE erroroffset;

  PCRE2_SPTR cpattern = (PCRE2_SPTR)pattern.c_str();

  logger_->debug("Compiling regex \"{}\"", pattern);

  pimpl_->re = pcre2_compile(cpattern,              /* the pattern */
                             PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
                             0,                     /* default options */
                             &errornumber,          /* for error number */
                             &erroroffset,          /* for error offset */
                             NULL);                 /* use default compile context */
  if (pimpl_->re == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
    throw RegexCompileException((int)erroroffset, std::string((char*)buffer));
  }
}

Regex::~Regex() {
  pcre2_match_data_free(pimpl_->match_data); /* Release memory used for the match */
  pcre2_code_free(pimpl_->re);
}

std::unique_ptr<IMatchIter> Regex::Search(const char* subject) {
  // free last match if available
  pcre2_match_data_free(pimpl_->match_data);

  int rc;
  int i;

  PCRE2_SIZE* ovector;

  auto subject_length = strlen((char*)subject);
  pimpl_->match_data = pcre2_match_data_create_from_pattern(pimpl_->re, NULL);
  rc = pcre2_match(pimpl_->re,          /* the compiled pattern */
                   (PCRE2_SPTR)subject, /* the subject string */
                   subject_length,      /* the length of the subject */
                   0,                   /* start at offset 0 in the subject */
                   0,                   /* default options */
                   pimpl_->match_data,  /* block for storing the result */
                   NULL);               /* use default match context */

  if (rc < 0) {
    switch (rc) {
      case PCRE2_ERROR_NOMATCH:
        break;

      /*
      Handle other special cases if you like
      */
      default:
        logger_->error("Matching error %d\n", rc);
        throw RegexSearchException(rc);
        break;
    }
    return std::make_unique<MatchIter>(nullptr, 0);
  }

  /* Match succeded. Get a pointer to the output vector, where string offsets are
  stored. */

  ovector = pcre2_get_ovector_pointer(pimpl_->match_data);
  /* The output vector wasn't big enough. This should not happen, because we used
  pcre2_match_data_create_from_pattern() above. */

  if (rc == 0) {
    logger_->error("ovector was not big enough for all the captured substring");
  }

  return std::make_unique<MatchIter>(pimpl_->match_data, rc);
}

