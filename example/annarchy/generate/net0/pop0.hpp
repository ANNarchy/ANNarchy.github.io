/*
 *  ANNarchy-version: 4.7.1
 */
#pragma once

#include "ANNarchy.h"
#include <random>

#include <opencv2/opencv.hpp>
using namespace cv;


extern double dt;
extern long int t;
extern std::vector<std::mt19937> rng;


// VideoPopulation
class CameraDeviceCPP : public cv::VideoCapture {
public:
    CameraDeviceCPP (int id, int width, int height, int depth) : cv::VideoCapture(id){
        width_ = width;
        height_ = height;
        depth_ = depth;
        img_ = std::vector<double>(width*height*depth, 0.0);
    }
    std::vector<double> GrabImage(){
        if(isOpened()){
            // Read a new frame from the video
            Mat frame;
            read(frame);
            // Resize the image
            Mat resized_frame;
            resize(frame, resized_frame, Size(width_, height_) );
            // If depth=1, only luminance
            if(depth_==1){
                // Convert to luminance
                cvtColor(resized_frame, resized_frame, COLOR_BGR2GRAY);
                for(int i = 0; i < resized_frame.rows; i++){
                    for(int j = 0; j < resized_frame.cols; j++){
                        this->img_[j+width_*i] = float(resized_frame.at<uchar>(i, j))/255.0;
                    }
                }
            }
            else{ //BGR
                for(int i = 0; i < resized_frame.rows; i++){
                    for(int j = 0; j < resized_frame.cols; j++){
                        Vec3b intensity = resized_frame.at<Vec3b>(i, j);
                        this->img_[(j+width_*i)*3 + 0] = double(intensity.val[2])/255.0;
                        this->img_[(j+width_*i)*3 + 1] = double(intensity.val[1])/255.0;
                        this->img_[(j+width_*i)*3 + 2] = double(intensity.val[0])/255.0;
                    }
                }
            }
        }
        return this->img_;
    };

protected:
    // Width and height of the image, depth_ is 1 (grayscale) or 3 (RGB)
    int width_, height_, depth_;
    // Vector of floats for the returned image
    std::vector<double> img_;
};

///////////////////////////////////////////////////////////////
// Main Structure for the population of id 0 (pop0)
///////////////////////////////////////////////////////////////
struct PopStruct0{

    int size; // Number of neurons
    bool _active; // Allows to shut down the whole population
    int max_delay; // Maximum number of steps to store for delayed synaptic transmission

    // Access functions used by cython wrapper
    int get_size() { return size; }
    void set_size(int s) { size  = s; }
    int get_max_delay() { return max_delay; }
    void set_max_delay(int d) { max_delay  = d; }
    bool is_active() { return _active; }
    void set_active(bool val) { _active = val; }



    // Neuron specific parameters and variables

    // Local parameter r
    std::vector< double > r;

    // Random numbers




    // Camera
    CameraDeviceCPP* camera_;
    void StartCamera(int id, int width, int height, int depth){
        camera_ = new CameraDeviceCPP(id, width, height, depth);
        if(!camera_->isOpened()){
            std::cout << "Error: could not open the camera." << std::endl;
        }
    };
    void GrabImage(){
        if(camera_->isOpened()){
            r = camera_->GrabImage();
        }
    };
    void ReleaseCamera(){
        camera_->release();
    };


    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter r
        if ( name.compare("r") == 0 ) {
            return r;
        }


        // should not happen
        std::cerr << "PopStruct0::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }


        // should not happen
        std::cerr << "PopStruct0::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct0::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct0::set_local_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct0::init_population(size="<<this->size<<") - this = " << this << std::endl;
    #endif
        _active = true;

        // Local parameter r
        r = std::vector<double>(size, 0.0);






    }

    // Method called to reset the population
    void reset() {



    }

    // Init rng dist
    void init_rng_dist() {

    }

    // Method to draw new random numbers
    void update_rng() {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "    PopStruct0::update_rng()" << std::endl;
#endif

    }

    // Method to update global operations on the population (min/max/mean...)
    void update_global_ops() {

    }

    // Method to enqueue output variables in case outgoing projections have non-zero delay
    void update_delay() {

    }

    // Method to dynamically change the size of the queue for delayed variables
    void update_max_delay(int value) {

    }

    // Main method to update neural variables
    void update() {

    }

    void spike_gather() {

    }



    // Memory management: track the memory consumption
    long int size_in_bytes() {
        long int size_in_bytes = 0;
        // Parameters
        size_in_bytes += sizeof(double) * r.capacity();	// r
        // Variables
        // RNGs

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct0::clear() - this = " << this << std::endl;
#endif
        // Variables

        // RNGs

    }
};

