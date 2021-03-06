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
/// \file FCC0PrimaryGeneratorAction.cc
/// \brief Implementation of the FCC0PrimaryGeneratorAction class

#include "FCC0PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0PrimaryGeneratorAction::FCC0PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fMessenger(0),
  fParticleGun(0),
  //fRandom(true)
  fRandom(false)
{   
  G4int nofParticles = 1;
  fParticleGun  = new G4ParticleGun(nofParticles);

  // Define particle properties
  G4String particleName = "pi+";
  //G4String particleName = "geantino";
  G4ThreeVector position(0, 0, 0.*m);   
  G4ThreeVector momentum(0, 1000.*GeV, 0);
  
  // Default particle kinematics
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentum(momentum);
  fParticleGun->SetParticlePosition(position);
  
  // Generic messenger
  // Define /B4/event commands using generic messenger class
  fMessenger 
    = new G4GenericMessenger(this, "/FCC0/primary/", "Primary generator control");

  // Define /B4/event/setPrintModulo command
  fMessenger
    ->DeclareProperty("setRandom", 
                      fRandom, 
                      "Activate/Inactivate random option");
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0PrimaryGeneratorAction::~FCC0PrimaryGeneratorAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  //this function is called at the begining of ecah event
  //

  if ( fRandom ) {
    // randomized direction
    G4double x = G4UniformRand();
    G4double y = G4UniformRand();
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, 0));
  }
  else {
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 1, 0));
  }  

  fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

