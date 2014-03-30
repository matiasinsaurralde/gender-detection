#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
};

int main(int argc, const char *argv[]) {
  string fn_csv = "model.csv";
  string fn_predict = argv[1];

  vector<Mat> modelImages;
  vector<int> modelLabels;

  read_csv( fn_csv, modelImages, modelLabels );

  Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
  model->train( modelImages, modelLabels );

  std::cout << "Finding match for '" << fn_predict << "'" << std::endl;
  Mat testImage =  imread(fn_predict, 0);

  int predictedLabel =-1;
  double predictedConfidence = 0.0;

  model->predict(testImage, predictedLabel, predictedConfidence);

  std::cout << "'" << fn_predict << "' => " << predictedLabel << std::endl;
  std::cout << "Confidence: " << predictedConfidence << std::endl;
};
