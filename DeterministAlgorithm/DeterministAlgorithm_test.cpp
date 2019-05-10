#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "DeterministAlgorithm.h"


TEST_CASE("Label generator is begin correctly performed"){

  std::vector<std::vector<int> > labels = DeterministAlgorithm::generateLabels(3);
  std::vector<std::vector<int> > labels_;

  std::vector<int> label1;
  label1.push_back(1);
  label1.push_back(2);
  label1.push_back(3);

  std::vector<int> label2;
  label2.push_back(2);
  label2.push_back(1);
  label2.push_back(3);

  std::vector<int> label6;
  label6.push_back(2);
  label6.push_back(3);
  label6.push_back(1);

  std::vector<int> label3;
  label3.push_back(3);
  label3.push_back(2);
  label3.push_back(1);

  std::vector<int> label5;
  label5.push_back(3);
  label5.push_back(1);
  label5.push_back(2);

  std::vector<int> label4;
  label4.push_back(1);
  label4.push_back(3);
  label4.push_back(2);

  labels_.push_back(label1);
  labels_.push_back(label2);
  labels_.push_back(label3);
  labels_.push_back(label4);
  labels_.push_back(label5);
  labels_.push_back(label6);

  bool isContained = false;
  for (int i = 0; i < labels_.size(); i++){
    isContained = false;
    for (int j = 0; j < labels.size(); j++){
      if(std::equal(labels_[i].begin(), labels_[i].end(), labels[j].begin())){
        isContained = true;
      }
    }
    if(!isContained){
      break;
    }
  }

  REQUIRE(isContained == true);
  REQUIRE(labels_.size() == labels.size());


}
