#ifndef SHOWERRECOSTUDY_CXX
#define SHOWERRECOSTUDY_CXX

#include "ShowerRecoStudy.h"
#include "DataFormat/mcshower.h"
#include "DataFormat/shower.h"
#include "GeoAlgo/GeoVector.h"

namespace larlite {

  bool ShowerRecoStudy::initialize() {

   if(!_ana_tree){

     _ana_tree = new TTree("ana_tree","ana_tree");
     _ana_tree->Branch("n_reco_showers",&_n_reco_showers,"n_reco_showers/I");
     _ana_tree->Branch("n_true_showers",&_n_true_showers,"n_true_showers/I");
     _ana_tree->Branch("reco_show_length",&_reco_show_length,"reco_show_length/D");
     _ana_tree->Branch("true_show_length",&_true_show_length,"true_show_length/D");
     _ana_tree->Branch("prof_show_length",&_prof_show_length,"prof_show_length/D");
     _ana_tree->Branch("reco_show_E",&_reco_show_E,"reco_show_E/D");
     _ana_tree->Branch("true_show_E",&_true_show_E,"true_show_E/D");
     _ana_tree->Branch("st_pt_diff",&_st_pt_diff,"st_pt_diff/D");
     _ana_tree->Branch("E_contained",&_E_contained,"E_contained/O");
   }

    return true;
  }
  
  bool ShowerRecoStudy::analyze(storage_manager* storage) {
  
    _n_reco_showers = 0;
    _n_true_showers = 0;
    _reco_show_length = -999.;
    _true_show_length = -999.;
    _prof_show_length = -999.;
    _reco_show_E = -999.;
    _true_show_E = -999.;
    _st_pt_diff = -1.;
    _E_contained = false;

    auto ev_mcs = storage->get_data<event_mcshower>("mcreco");
    if(!ev_mcs){
      print(larlite::msg::kERROR,__FUNCTION__,Form("Did not find specified data product, MCShower!"));
      return false;
    }
    
    auto ev_s = storage->get_data<event_shower>("newdefaultreco");
    if(!ev_s){
      print(larlite::msg::kERROR,__FUNCTION__,Form("Did not find specified data product, Shower!"));
      return false;
    }
    
    _n_reco_showers = ev_s->size();
    _n_true_showers = ev_mcs->size();

    if(_n_reco_showers == 1 && _n_true_showers == 1){

      _reco_show_length = ev_s->at(0).Length();
      // temporary fix after bug in pitch units was found
      _reco_show_length /= 0.3;
      _true_show_length = geoalgo::Vector(ev_mcs->at(0).End().Position()).Dist(geoalgo::Vector(ev_mcs->at(0).Start().Position()) );
      _prof_show_length = _shrProfiler.Length( ev_s->at(0).Energy().at(2));
      _reco_show_E = ev_s->at(0).Energy().at(2);
      _true_show_E = ev_mcs->at(0).DetProfile().E();
      _st_pt_diff = geoalgo::Vector(ev_mcs->at(0).Start().Position()).Dist(geoalgo::Vector(ev_s->at(0).ShowerStart()));
      _E_contained = ( ( ev_mcs->at(0).DetProfile().E() / ev_mcs->at(0).Start().E() ) > 0.95 ) ? true : false;
    }
    
    _ana_tree->Fill();

    return true;
  }

  bool ShowerRecoStudy::finalize() {

    if(_fout){
      _fout->cd();
      if(_ana_tree)
	_ana_tree->Write();

    }  
    return true;
  }

}
#endif
