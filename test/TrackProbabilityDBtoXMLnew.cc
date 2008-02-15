// -*- C++ -*-
//
// Package:    TrackProbabilityDBtoXMLnew
// Class:      TrackProbabilityDBtoXMLnew
// 
/**\class TrackProbabilityDBtoXMLnew TrackProbabilityDBtoXMLnew.cc RecoBTag/TrackProbabilityDBtoXMLnew/src/TrackProbabilityDBtoXMLnew.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andrea Rizzi
//         Created:  Wed Apr 12 11:12:49 CEST 2006
// $Id: TrackProbabilityDBtoXMLnew.cc,v 1.2 2007/10/01 08:00:37 arizzi Exp $
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
 
#include <boost/shared_ptr.hpp>

#include <TClass.h>
#include <TBufferXML.h>



// system include files
#include <memory>
#include <string>
#include <iostream>
using namespace std;

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/BTauReco/interface/JetTracksAssociation.h"

//#include "RecoBTag/TrackProbability/interface/TrackClassFilterCategory.h"

#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include "TrackProbabilityCalibratedHistogram.h"

#include "RecoBTag/BTagTools/interface/SignedTransverseImpactParameter.h"
#include "RecoBTag/BTagTools/interface/SignedImpactParameter3D.h"
#include "RecoBTag/BTagTools/interface/SignedDecayLength3D.h"

//CondFormats
#include "CondFormats/BTauObjects/interface/TrackProbabilityCalibration.h"

#include "FWCore/Framework/interface/IOVSyncValue.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
// Math
#include "Math/GenVector/VectorUtil.h"
#include "Math/GenVector/PxPyPzE4D.h"

#include "RecoBTag/XMLCalibration/interface/AlgorithmCalibration.h"
#include "RecoBTag/XMLCalibration/interface/CalibratedHistogramXML.h"

//#include "TH1F.h"
//#include "TFile.h"

#include "CondFormats/BTauObjects/interface/TrackProbabilityCalibration.h"
#include "RecoBTag/XMLCalibration/interface/CalibrationInterface.h"
#include "CondFormats/DataRecord/interface/BTagTrackProbability2DRcd.h"
#include "CondFormats/DataRecord/interface/BTagTrackProbability3DRcd.h"
#include "FWCore/Framework/interface/EventSetupRecord.h"
#include "FWCore/Framework/interface/EventSetupRecordImplementation.h"
#include "FWCore/Framework/interface/EventSetupRecordKey.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <fstream>
#include <iostream>

using namespace reco;
using namespace edm;

using namespace std;
//
// class decleration
//

class TrackProbabilityDBtoXMLnew : public edm::EDAnalyzer {
   public:
      explicit TrackProbabilityDBtoXMLnew(const edm::ParameterSet&);

    virtual void endJob()
    {


    std::ofstream ofile("2d.dat");
    TBuffer buffer(TBuffer::kWrite);
    buffer.StreamObject(const_cast<void*>(static_cast<const void*>(ca2D)),
                                                  TClass::GetClass("TrackProbabilityCalibration"));
    Int_t size = buffer.Length();
     ofile.write(buffer.Buffer(),size);
   ofile.close(); 

    std::ofstream ofile3("3d.dat");
    TBuffer buffer3(TBuffer::kWrite);
    buffer3.StreamObject(const_cast<void*>(static_cast<const void*>(ca3D)),
                                                  TClass::GetClass("TrackProbabilityCalibration"));
    Int_t size3 = buffer3.Length();
     ofile3.write(buffer3.Buffer(),size3);
   ofile3.close();


 std::ofstream of2("2d.xml");
   TBufferXML a(TBuffer::kWrite);
   of2 << a.ConvertToXML(const_cast<void*>(static_cast<const void*>(ca2D)),
                                                  TClass::GetClass("TrackProbabilityCalibration"),
                                                  kTRUE, kFALSE);

   of2.close();



 std::ofstream of3("3d.xml");
   TBufferXML b(TBuffer::kWrite);
   of3 << b.ConvertToXML(const_cast<void*>(static_cast<const void*>(ca3D)),
                                                  TClass::GetClass("TrackProbabilityCalibration"),
                                                  kTRUE, kFALSE);

   of3.close();




    }    
      ~TrackProbabilityDBtoXMLnew() 
    {
    }



      virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
     {

   ESHandle<TrackProbabilityCalibration> calib2DHandle;
   iSetup.get<BTagTrackProbability2DRcd>().get(calib2DHandle);
   ESHandle<TrackProbabilityCalibration> calib3DHandle;
   iSetup.get<BTagTrackProbability3DRcd>().get(calib3DHandle);

    ca2D= calib2DHandle.product();
    ca3D= calib3DHandle.product();


     }
 private:
    const TrackProbabilityCalibration * ca2D;
  const TrackProbabilityCalibration * ca3D;


};

//
// constructors and destructor
//
TrackProbabilityDBtoXMLnew::TrackProbabilityDBtoXMLnew(const edm::ParameterSet& parameters)
{
}


//define this as a plug-in
DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE(TrackProbabilityDBtoXMLnew);
