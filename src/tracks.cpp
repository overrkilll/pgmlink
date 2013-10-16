#include "pgmlink/tracks.h"

namespace pgmlink {

////
//// Class Track
////
Track::Track() {
}

Track::Track(size_t id, size_t time_start, const Traxelvector& traxels)
: id_(id), time_start_(time_start), traxels_(traxels) {
}

void Track::set_id(const size_t id) {
  id_ = id;
}

size_t Track::get_id() const {
  return Track::id_;
}

void Track::set_time_start(const size_t time_start) {
  time_start_ = time_start;
}

size_t Track::get_time_start() const {
  return Track::time_start_;
}

size_t Track::get_length() const {
  return Track::traxels_.size();
}

////
//// Class TrackFeatureExtractor
////
TrackFeatureExtractor::TrackFeatureExtractor(
  boost::shared_ptr<FeatureCalculator> calculator,
  const std::string& feature_name,
  const FeatureOrder order 
) :
  calculator_(calculator),
  extractor_(new FeatureExtractor(calculator, feature_name)),
  feature_name_(feature_name),
  order_(order) {
}

feature_arrays TrackFeatureExtractor::extract(const Track& track) const {
  size_t tracklength = track.get_length(); 
  assert(tracklength-order_ > 0);

  feature_arrays ret;
  Traxelvector::const_iterator traxel_it;

  for (
    traxel_it = track.traxels_.begin();
    traxel_it+order_ != track.traxels_.end();
    traxel_it++
  ) {
    switch(order_) {
      case SINGLE:
        ret.push_back(extractor_->extract(*traxel_it));
        break;
      case PAIRWISE:
        ret.push_back(extractor_->extract(*traxel_it, *(traxel_it+1)));
        break;
      case TRIPLET:
        ret.push_back(extractor_->extract(*traxel_it, *(traxel_it+1), *(traxel_it+2)));
    }
  }
  return ret;
}

FeatureOrder TrackFeatureExtractor::get_feature_order() const {
  return TrackFeatureExtractor::order_;
}


} // namespace pgmlink