//   $Main author: Guillermo Casas
//

// Project includes

// System includes
#include <limits>
#include <iostream>
#include <iomanip>

// External includes
#ifdef _OPENMP
#include <omp.h>
#endif

// Project includes
#include "analytic_face_watcher.h"
#include "DEM_application.h"

namespace Kratos
{

typedef ModelPart::ConditionsContainerType::iterator ConditionsIteratorType;
typedef AnalyticRigidFace3D AnalyticFace;

void AnalyticFaceWatcher::MakeMeasurements(ModelPart& analytic_model_part)
{
    const double current_time = analytic_model_part.GetProcessInfo()[TIME];
    ImpactsTimeStepDataBase time_step_database(current_time);

    for (ConditionsIteratorType i_cond = analytic_model_part.ConditionsBegin(); i_cond != analytic_model_part.ConditionsEnd(); ++i_cond){
        AnalyticFace& face = dynamic_cast<Kratos::AnalyticRigidFace3D&>(*(*(i_cond.base())));
        const int n_collisions = face.GetNumberOfCrossings();

        if (n_collisions){
            const int id = int(i_cond->Id());
            FaceHistoryDatabase& face_database = GetFaceDataBase(id);
            std::vector<int> colliding_ids = face.GetSignedCollidingIds();
            std::vector<double> colliding_normal_vel = face.GetCollidingNormalRelativeVelocity();
            std::vector<double> colliding_tangential_vel = face.GetCollidingTangentialRelativeVelocity();

            for (int i = 0; i < n_collisions; ++i){
                time_step_database.PushBackImpacts(id, colliding_ids[i], colliding_normal_vel[i], colliding_tangential_vel[i]);
                face_database.PushBackImpacts(current_time, colliding_ids[i], colliding_normal_vel[i], colliding_tangential_vel[i]);
            }
        }
    }

    mVectorOfTimeStepDatabases.push_back(time_step_database);

    if (time_step_database.GetNumberOfImpacts()){

    }
}

void AnalyticFaceWatcher::ClearList(boost::python::list& my_list)
{
    while(len(my_list)){
        my_list.pop(); // only way I found to remove all entries
    }
}

void AnalyticFaceWatcher::GetFaceData(int id,
                                      boost::python::list times,
                                      boost::python::list neighbour_ids,
                                      boost::python::list normal_relative_vel,
                                      boost::python::list tangential_relative_vel)
{
    mMapOfFaceHistoryDatabases[id].FillUpPythonLists(times, neighbour_ids, normal_relative_vel, tangential_relative_vel);
}

void AnalyticFaceWatcher::GetAllFacesData(ModelPart& analytic_model_part,
                                          boost::python::list times,
                                          boost::python::list neighbour_ids,
                                          boost::python::list normal_relative_vel,
                                          boost::python::list tangential_relative_vel)
{
    ClearList(times);
    ClearList(neighbour_ids);
    ClearList(normal_relative_vel);
    ClearList(tangential_relative_vel);

    for (ConditionsIteratorType i_cond = analytic_model_part.ConditionsBegin(); i_cond != analytic_model_part.ConditionsEnd(); ++i_cond){
        boost::python::list times_i;
        boost::python::list neighbour_ids_i;
        boost::python::list normal_relative_vel_i;
        boost::python::list tangential_relative_vel_i;
        const int id = int(i_cond->Id());
        GetFaceData(id, times_i, neighbour_ids_i, normal_relative_vel_i, tangential_relative_vel_i);
        times.append(times_i);
        neighbour_ids.append(neighbour_ids_i);
        normal_relative_vel.append(normal_relative_vel_i);
        tangential_relative_vel.append(tangential_relative_vel_i);
    }

}

void AnalyticFaceWatcher::GetTimeStepsData(boost::python::list ids,
                                               boost::python::list neighbour_ids,
                                               boost::python::list normal_relative_vel,
                                               boost::python::list tangential_relative_vel)
{
    ClearList(ids);
    ClearList(neighbour_ids);
    ClearList(normal_relative_vel);
    ClearList(tangential_relative_vel);
    const int n_time_steps = mVectorOfTimeStepDatabases.size();

    for (int i = 0; i < n_time_steps; ++i){
        boost::python::list ids_i;
        boost::python::list neighbour_ids_i;
        boost::python::list normal_relative_vel_i;
        boost::python::list tangential_relative_vel_i;
        mVectorOfTimeStepDatabases[i].FillUpPythonLists(ids_i, neighbour_ids_i, normal_relative_vel_i, tangential_relative_vel_i);
        ids.append(ids_i);
        neighbour_ids.append(neighbour_ids_i);
        normal_relative_vel.append(normal_relative_vel_i);
        tangential_relative_vel.append(tangential_relative_vel_i);
    }
}


AnalyticFaceWatcher::FaceHistoryDatabase& AnalyticFaceWatcher::GetFaceDataBase(int id)
{
    if (mMapOfFaceHistoryDatabases.find(id) == mMapOfFaceHistoryDatabases.end()){
      AnalyticFaceWatcher::FaceHistoryDatabase new_face_database(id);
      mMapOfFaceHistoryDatabases[id] = new_face_database;
    }

    return mMapOfFaceHistoryDatabases[id];
}

/// Turn back information as a string.
std::string AnalyticFaceWatcher::Info() const {
        return "AnalyticFaceWatcher";
}

/// Print information about this object.
void AnalyticFaceWatcher::PrintInfo(std::ostream& rOStream) const {}

/// Print object's data.
void AnalyticFaceWatcher::PrintData(std::ostream& rOStream) const {}


} // namespace Kratos
