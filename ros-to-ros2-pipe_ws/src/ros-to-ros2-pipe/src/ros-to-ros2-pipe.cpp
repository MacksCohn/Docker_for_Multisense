#include "rclcpp/rclcpp.hpp"
#include "ros/ros.h"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/msg/point_field.hpp"
#include "pcl_conversions/pcl_conversions.h"

class Pipe : public rclcpp::Node {
private:
    ros::Subscriber _intake_points;
    ros::Subscriber _intake_image_left;
    ros::Subscriber _intake_image_right;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr _output_points;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr _output_image_left;
    // rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr _output_image_right;
    ros::NodeHandle _n;

    void _on_intake_points(sensor_msgs::PointCloud2 cloud) {
        sensor_msgs::msg::PointCloud2 converted;
        converted.header.frame_id = "camera_link";
        converted.header.stamp = get_clock()->now();
        // RCLCPP_INFO(get_logger(), "%d", cloud.data.size());
        sensor_msgs::msg::PointField temp;
        temp.name     = cloud.fields[0].name;
        temp.offset   = cloud.fields[0].offset;
        temp.datatype = cloud.fields[0].datatype;
        temp.count    = cloud.fields[0].count;
        converted.fields.push_back(temp);
        temp.name     = cloud.fields[1].name;
        temp.offset   = cloud.fields[1].offset;
        temp.datatype = cloud.fields[1].datatype;
        temp.count    = cloud.fields[1].count;
        converted.fields.push_back(temp);
        temp.name     = cloud.fields[2].name;
        temp.offset   = cloud.fields[2].offset;
        temp.datatype = cloud.fields[2].datatype;
        temp.count    = cloud.fields[2].count;
        converted.fields.push_back(temp);
        temp.name     = cloud.fields[3].name;
        temp.offset   = cloud.fields[3].offset;
        temp.datatype = cloud.fields[3].datatype;
        temp.count    = cloud.fields[3].count;
        converted.fields.push_back(temp);

        converted.height = cloud.height;
        converted.width = cloud.width;
        converted.is_bigendian = cloud.is_bigendian;
        converted.point_step = cloud.point_step;
        converted.row_step = cloud.row_step;
        converted.is_dense = cloud.is_dense;
        converted.data = cloud.data;
        _output_points->publish(converted);
    }
    void _on_intake_image_left(sensor_msgs::Image img) {
        sensor_msgs::msg::Image converted;
        converted.header.frame_id=img.header.frame_id;
        converted.header.stamp = get_clock()->now();
        converted.data = img.data;
        converted.step = img.step;
        converted.is_bigendian = img.is_bigendian;
        converted.width = img.width;
        converted.height = img.height;
        converted.encoding = img.encoding;
        _output_image_left->publish(converted);
    }
    void _on_intake_image_right(sensor_msgs::Image img) {
        sensor_msgs::msg::Image converted;
        converted.header.frame_id=img.header.frame_id;
        converted.header.stamp = get_clock()->now();
        converted.data = img.data;
        converted.step = img.step;
        converted.is_bigendian = img.is_bigendian;
        converted.width = img.width;
        converted.height = img.height;
        converted.encoding = img.encoding;
        // _output_image_right->publish(converted);
    }
public:
    Pipe() : Node("rosToRos2Pipe") {
        _intake_points = _n.subscribe("multisense/image_points2", 1, &Pipe::_on_intake_points, this);
        _intake_image_left = _n.subscribe("multisense/left/image_color", 1, &Pipe::_on_intake_image_left, this);
        // _intake_image_right = _n.subscribe("multisense/right/image_rect", 1, &Pipe::_on_intake_image_right, this);
        _output_points = this->create_publisher<sensor_msgs::msg::PointCloud2>("multisense/image_points2", 10);
        _output_image_left = this->create_publisher<sensor_msgs::msg::Image>("multisense/left/image_color", 10);
        // _output_image_right = this->create_publisher<sensor_msgs::msg::Image>("multisense/right/image_color", 10);
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    ros::init(argc,argv, "Pipe");
    ros::AsyncSpinner spinner(4);
    spinner.start();
    rclcpp::spin(std::make_shared<Pipe>());
    rclcpp::shutdown();
    ros::shutdown();
    return 0;
}