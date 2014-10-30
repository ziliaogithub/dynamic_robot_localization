/**\file outlier_detector.hpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <dynamic_robot_localization/outlier_detectors/outlier_detector.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace dynamic_robot_localization {

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <imports>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </imports>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// =============================================================================  <public-section>  ============================================================================
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructor>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructor>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <OutlierDetector-functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<typename PointT>
void OutlierDetector<PointT>::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle, ros::NodeHandlePtr& private_node_handle, std::string configuration_namespace) {
	std::string aligned_pointcloud_outliers_publish_topic, final_param_name;
	if (ros::param::search(private_node_handle->getNamespace() + "/" + configuration_namespace, "aligned_pointcloud_outliers_publish_topic", final_param_name)) {
		private_node_handle->param(final_param_name, aligned_pointcloud_outliers_publish_topic, std::string(""));
	}

	std::string aligned_pointcloud_inliers_publish_topic;
	if (ros::param::search(private_node_handle->getNamespace() + "/" + configuration_namespace, "aligned_pointcloud_inliers_publish_topic", final_param_name)) {
		private_node_handle->param(final_param_name, aligned_pointcloud_inliers_publish_topic, std::string(""));
	}

	if (!aligned_pointcloud_outliers_publish_topic.empty()) {
		outliers_publisher_ = node_handle->advertise<sensor_msgs::PointCloud2>(aligned_pointcloud_outliers_publish_topic, 1, true);
	}

	if (!aligned_pointcloud_inliers_publish_topic.empty()) {
		inliers_publisher_ = node_handle->advertise<sensor_msgs::PointCloud2>(aligned_pointcloud_inliers_publish_topic, 1, true);
	}
}


template<typename PointT>
bool OutlierDetector<PointT>::isPublishingOutliers() {
	return !outliers_publisher_.getTopic().empty();
}


template<typename PointT>
bool OutlierDetector<PointT>::isPublishingInliers() {
	return !inliers_publisher_.getTopic().empty();
}


template<typename PointT>
void OutlierDetector<PointT>::publishOutliers(typename pcl::PointCloud<PointT>::Ptr& outliers) {
	if (!outliers->empty() && isPublishingOutliers()) {
		sensor_msgs::PointCloud2Ptr outliers_msg(new sensor_msgs::PointCloud2());
		pcl::toROSMsg(*outliers, *outliers_msg);
		outliers_publisher_.publish(outliers_msg);
	}
}


template<typename PointT>
void OutlierDetector<PointT>::publishInliers(typename pcl::PointCloud<PointT>::Ptr& inliers) {
	if (!inliers->empty() && isPublishingInliers()) {
		sensor_msgs::PointCloud2Ptr inliers_msg(new sensor_msgs::PointCloud2());
		pcl::toROSMsg(*inliers, *inliers_msg);
		inliers_publisher_.publish(inliers_msg);
	}
}
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </OutlierDetector-functions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// =============================================================================  </public-section>  ===========================================================================

// =============================================================================   <protected-section>   =======================================================================
// =============================================================================   </protected-section>  =======================================================================

// =============================================================================   <private-section>   =========================================================================
// =============================================================================   </private-section>  =========================================================================

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <template instantiations>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </template instantiations>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

} /* namespace dynamic_robot_localization */


