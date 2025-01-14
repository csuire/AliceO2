// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "EMCALBase/Hit.h"

ClassImp(o2::emcal::Hit);

using namespace o2::emcal;

void Hit::PrintStream(std::ostream& stream) const
{
  stream << "EMCAL point: Track " << GetTrackID() << " in detector segment " << GetDetectorID()
         << " at position (" << GetX() << "|" << GetY() << "|" << GetZ() << "), energy loss " << GetEnergyLoss()
         << ", initial (parent) energy " << mInitialEnergy;
}

Bool_t Hit::operator<(const Hit& rhs) const
{
  if (GetTrackID() != rhs.GetTrackID()) {
    return GetTrackID() < rhs.GetTrackID();
  }
  return GetDetectorID() < rhs.GetDetectorID();
}

Bool_t Hit::operator==(const Hit& rhs) const
{
  return (GetDetectorID() == rhs.GetDetectorID()) && (GetTrackID() == rhs.GetTrackID());
}

Hit& Hit::operator+=(const Hit& rhs)
{
  SetEnergyLoss(GetEnergyLoss() + rhs.GetEnergyLoss());
  return *this;
}

Hit o2::emcal::operator+(const Hit& lhs, const Hit& rhs)
{
  Hit result(lhs);
  result.SetEnergyLoss(result.GetEnergyLoss() + rhs.GetEnergyLoss());
  return result;
}

std::ostream& o2::emcal::operator<<(std::ostream& stream, const Hit& p)
{
  p.PrintStream(stream);
  return stream;
}
