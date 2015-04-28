/**
 * \file NuEnergyReco.h
 *
 * \ingroup scratch_ana
 * 
 * \brief Class def header for a class NuEnergyReco
 *
 * @author davidkaleko
 */

/** \addtogroup scratch_ana

    @{*/

#ifndef LARLITE_NUENERGYRECO_H
#define LARLITE_NUENERGYRECO_H

#include "Analysis/ana_base.h"
#include "DataFormat/mcpart.h"
#include "TTree.h"

namespace larlite {
  /**
     \class NuEnergyReco
     User custom analysis class made by davidkaleko
   */
  class NuEnergyReco : public ana_base{
  
  public:

    /// Default constructor
    NuEnergyReco(){ _name="NuEnergyReco"; tree=0; _fout=0;};

    /// Default destructor
    virtual ~NuEnergyReco(){};

    /** IMPLEMENT in NuEnergyReco.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in NuEnergyReco.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in NuEnergyReco.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    protected:

    void ResetTTreeVars();

    double ComputeNuEFromMCPart(const std::vector<larlite::mcpart> &myparts);
    double ComputeTotalInitialE(const std::vector<larlite::mcpart> &myparts);
    double ComputeTotalFinalE(const std::vector<larlite::mcpart> &myparts);
    
    TTree* tree;
    double nu_E_from_mcnu;
    double nu_vtx_x_from_mcnu;
    double nu_vtx_y_from_mcnu;
    double nu_vtx_z_from_mcnu;

    double nu_E_from_mcpart;
    double nu_vtx_x_from_mcpart;
    double nu_vtx_y_from_mcpart;
    double nu_vtx_z_from_mcpart;

    double remnant_E;

    double tot_mcs_E;
    double tot_mct_E;
    int n_mcs;
    int n_mct;

    double tot_initial_E;
    double tot_final_E;
    
    double non_mcs_mct_E;
    int n_non_mcs_mct;

    int nuance_intxn;
    int hit_target;
    int hit_nuc;

    int nu_pdg;
  };
}
#endif
