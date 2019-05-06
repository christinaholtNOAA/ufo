/*
 * (C) Copyright 2018-2019 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#ifndef UFO_QCMANAGER_H_
#define UFO_QCMANAGER_H_

#include <ostream>

#include "boost/shared_ptr.hpp"

#include "eckit/config/LocalConfiguration.h"
#include "ioda/ObsDataVector.h"
#include "ioda/ObsSpace.h"
#include "oops/base/Variables.h"
#include "oops/util/Printable.h"

namespace ioda {
  class ObsVector;
}

namespace ufo {
class GeoVaLs;

class QCmanager : public util::Printable {
 public:
  QCmanager(ioda::ObsSpace &, const eckit::Configuration &,
            boost::shared_ptr<ioda::ObsDataVector<int> >,
            boost::shared_ptr<ioda::ObsDataVector<float> >);
  ~QCmanager();

  void priorFilter(const GeoVaLs &) const {}
  void postFilter(const ioda::ObsVector &) const;

  const oops::Variables & requiredGeoVaLs() const {return nogeovals_;}

 private:
  void print(std::ostream &) const;

  ioda::ObsSpace & obsdb_;
  const eckit::LocalConfiguration config_;
  const oops::Variables nogeovals_;
  ioda::ObsDataVector<int> & flags_;
  boost::shared_ptr<ioda::ObsDataVector<float> > obserr_;
};

}  // namespace ufo

#endif  // UFO_QCMANAGER_H_