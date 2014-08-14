//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file FCC0EmCalorimeterSD.hh
/// \brief Definition of the FCC0EmCalorimeterSD class
//

#ifndef FCC0EmCalorimeterSD_h
#define FCC0EmCalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "FCC0EmCalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class FCC0EmCalorimeterSD : public G4VSensitiveDetector
{
public:
  FCC0EmCalorimeterSD(const G4String& name, 
		    const G4String& hitsCollectionName,
		    const G4int& Nlayers);
  virtual ~FCC0EmCalorimeterSD();
  
  virtual void   Initialize(G4HCofThisEvent* hce);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hce);
  
private:
  FCC0EmCalorimeterHitsCollection* fHitsCollection;
  G4int fNlayers;
};




#endif

