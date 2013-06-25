#ifndef MULTI_HYPOTHESES_SEGMENTATION_H
#define MULTI_HYPOTHESES_SEGMENTATION_H

// stl
#include <vector>

// vigra
#include <vigra/multi_array.hxx>

// boost
#include <boost/shared_ptr.hpp>

// pgmlink
#include <pgmlink/clustering.h>
#include <pgmlink/traxels.h>


namespace pgmlink {
  class MultiSegmenter;
  
  
  class MultiSegmenterBuilder;


  typedef boost::shared_ptr<ClusteringMlpackBase> ClusteringPtr;


  typedef boost::shared_ptr<ClusteringMlpackBuilderBase> ClusteringBuilderPtr;


  typedef boost::shared_ptr<MultiSegmenter> MultiSegmenterPtr;




  ////
  //// MultiSegmenter
  ////
  class MultiSegmenter {
  private:
    const std::vector<unsigned>& n_clusters_;
    ClusteringPtr clusterer_;
    MultiSegmenter();
  public:
    MultiSegmenter(const std::vector<unsigned>& n_clusters,
                   ClusteringPtr clusterer);
    vigra::MultiArrayView<2, unsigned> operator()();
  };


  ////
  //// MultiSegmenterBuilder
  ////
  class MultiSegmenterBuilder {
  private:
    const std::vector<unsigned>& n_clusters_;
    ClusteringBuilderPtr clustering_builder_;
  public:
    MultiSegmenterBuilder();
    MultiSegmenterBuilder(std::vector<unsigned> n_clusters,
                           ClusteringBuilderPtr clustering_builder);
    MultiSegmenterPtr build(const feature_array& data);
  };

}

#endif /* MULTI_HYPOTHESES_SEGMENTATION_H */
