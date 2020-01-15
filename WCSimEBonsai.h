#ifndef __WCSIMEBONSAI_H__
#define __WCSIMEBONSAI_H__

#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "WCSimRootGeom.hh"

using std::vector;

// ****************************************
// ** Energy estimation for a trigger    **
// ****************************************
// For a detailed description of the energy estimation formulas in SK-IV, see ch. 4.3 of
// http://www-sk.icrr.u-tokyo.ac.jp/sk/_pdf/articles/2016/doc_thesis_naknao.pdf

class WCSimEBonsai {

 public:
  WCSimEBonsai(const char * detectorname, WCSimRootGeom * geom, int verbose);
  ~WCSimEBonsai() {};

  float GetEnergy(std::vector<float> times, std::vector<int> tubeIds, float * vertex);

  //override default values with these methods
  void SetDarkRate(float darkrate);
  void SetNPMTs   (int npmts);
  void SetNWorkingPMTs(int nworkingpmts);
  void SetNeighbourDistance(float neighbourdistance);
  void SetShortDuration(float shortduration);
  void SetLongDuration(float longduration);
  void SetTopBottomDistance(float hi, float lo);

 private:
  enum kDetector_t {kSuperK = 0, kHyperK40, kHyperK20};

  kDetector_t DetectorEnumFromString(std::string name);
  void CorrectHitTimes();
  void FindMaxTimeInterval();
  void GetNearestNeighbours();
  void GetNEff();
  void CorrectEnergy();

  const float fLightGroupSpeed;
  const float fLambdaEff;
  static const float fEffCoverages[9];

  std::string fDetectorName;
  kDetector_t fDetector;
  float    fDarkRate;
  int       fNPMTs;
  int       fNWorkingPMTs;
  float    fNeighbourDistance;
  float    fTopBottomDistanceHi;
  float    fTopBottomDistanceLo;
  int       fVerbose;

  WCSimRootGeom * fGeom;

  int    fNDigits;
  int    fNMaxShort;
  int    fNMaxLong;
  float fLongDuration;
  float fShortDuration;
  float fStartTime;
  float  fVertex[4];

  float fNEff;
  float fNEff2;
  float fERec;

  vector<int>    fTubeIds;
  vector<float> fDistance;
  vector<float>  fTimes;
  vector<float>  fTimesCorrected;
  vector<float>  fTimesCorrectedSorted;

  vector<float> fDistanceShort;
  vector<float> fTubeIdsShort;

  std::map<int, std::vector<int> > fNeighbours;
};

#endif //__WCSIMEBONSAI_H__
