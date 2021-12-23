#include "cartographer/transform/transform.h"
#include "cartographer/io/proto_stream_deserializer.h"
#include "cartographer_ros/msg_conversion.h"
#include "cartographer_ros/time_conversion.h"
#include "geometry_msgs/Transform.h"

using namespace cartographer_ros;

geometry_msgs::Transform ToTransform(
        const cartographer::transform::proto::Rigid3d& parent_T_child) {
    geometry_msgs::Transform transform;
    //transform_stamped.header.stamp = cartographer_ros::ToRos(
    //    ::cartographer::common::FromUniversal(timestamp_uts));
    transform = cartographer_ros::ToGeometryMsgTransform(
        ::cartographer::transform::ToRigid3(parent_T_child));
    return transform;
}

void pbstream_trajectories_to_txt(const std::string& pbstream_filename,
                                    const std::string& output_txt_filename) {
    const auto pose_graph =
        cartographer::io::DeserializePoseGraphFromFile(pbstream_filename);
    static int64_t seq = 0;
    FILE* file = fopen(output_txt_filename.c_str(), "w");
    printf("pose_graph.trajectory().size(): %d\n", pose_graph.trajectory().size());
    for (const auto trajectory : pose_graph.trajectory()) {
        printf("trajectory.node().size(): %d\n", trajectory.node().size());
        for (const auto& node : trajectory.node()) {
        //tf::Quaternion q;
        geometry_msgs::Transform transform = ToTransform(node.pose());
        fprintf(file, "%f %f %f %f %f %f %f %f\n",
                cartographer_ros::ToRos(::cartographer::common::FromUniversal(node.timestamp())).toSec(),
                transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w,
                transform.translation.x, transform.translation.y, transform.translation.z);
        }
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: pbstream_node input output\n");
        exit(-1);
    }

    pbstream_trajectories_to_txt(argv[1], argv[2]);
    return 0;
}