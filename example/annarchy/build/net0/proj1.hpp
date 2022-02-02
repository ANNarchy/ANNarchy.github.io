/*
 *  ANNarchy-version: 4.7.1
 */
#pragma once

#include "ANNarchy.h"
#include "Specific.hpp"




extern PopStruct1 pop1;
extern PopStruct2 pop2;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj1: pop1 -> pop2 with target exc
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct1 : SpecificConnectivity {
    ProjStruct1() : SpecificConnectivity() {
    }




    // Connectivity data
    std::vector<int> post_rank;
    std::vector< std::vector<int> > pre_coords;


    // Accessor to connectivity data
    std::vector<int> get_post_rank() { return post_rank; }
    void set_post_rank(std::vector<int> ranks) { post_rank = ranks; }
    std::vector<std::vector<int>> get_pre_coords() { return pre_coords; }
    void set_pre_coords(std::vector<std::vector<int>> coords) { pre_coords = coords; }
    int nb_synapses() { return 0; } // TODO: filter-dim * number of filters?
    int dendrite_size(int n) { return 0; } // TODO: filter-dim?
    int nb_dendrites() { return post_rank.size(); }


    // Transmission and plasticity flags
    bool _transmission, _plasticity, _update;
    int _update_period;
    long int _update_offset;




    std::vector< std::vector< std::vector< double > > > w;



    // Method called to allocate/initialize the variables
    bool init_attributes() {




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct1::init_projection() - this = " << this << std::endl;
    #endif

        _transmission = true;
        _update = true;
        _plasticity = true;
        _update_period = 1;
        _update_offset = 0L;

        init_attributes();



    }

    // Spiking networks: reset the ring buffer when non-uniform
    void reset_ring_buffer() {

    }

    // Spiking networks: update maximum delay when non-uniform
    void update_max_delay(int d){

    }

    // Computes the weighted sum of inputs or updates the conductances
    void compute_psp() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct1::compute_psp()" << std::endl;
    #endif

        int rk_pre;
        double sum=0.0;


        if ( _transmission && pop1._active ) {
            int* coord;


            for(int i = 0; i < 3072; i++){
                coord = pre_coords[i].data();

                // perform the convolution
                sum = 0.0;

                for(int i_w = 0; i_w < 1;i_w++) {
                    int i_pre = coord[0] + (i_w - 0);
                    if ((i_pre < 0) || (i_pre > 47)){
                        sum += 0.0;
                        continue;
                    }

                    for(int j_w = 0; j_w < 1;j_w++) {
                        int j_pre = coord[1] + (j_w - 0);
                        if ((j_pre < 0) || (j_pre > 63)){
                            sum += 0.0;
                            continue;
                        }
                        auto inner_line = w[i_w][j_w].data();

                        for(int k_w = 0; k_w < 3;k_w++) {
                            int k_pre = coord[2] + (k_w - 1);
                            if ((k_pre < 0) || (k_pre > 2)){
                                sum += 0.0;
                                continue;
                            }

                            rk_pre = 3*(64*(i_pre) + j_pre) + k_pre;
                            sum += pop1.r[rk_pre]*inner_line[k_w];
                        }
                    }
                }

                // store result
                pop2._sum_exc[i] += sum;
            } // for
        } // if

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct1::update_synapse()" << std::endl;
    #endif


    }

    // Post-synaptic events
    void post_event() {


    }

    // Variable/Parameter access methods

    // Local parameter w
    std::vector< std::vector< std::vector< double > > > get_w() { return w; }
    void set_w(std::vector< std::vector< std::vector< double > > > value) { w = value; }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // post-ranks
        size_in_bytes += sizeof(std::vector<int>);
        size_in_bytes += post_rank.capacity() * sizeof(int);

        // pre-coords
        size_in_bytes += sizeof(std::vector<std::vector<int>>);
        size_in_bytes += pre_coords.capacity() * sizeof(std::vector<int>);
        for (auto it = pre_coords.begin(); it != pre_coords.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(int);
        }

        // filter
        // TODO:

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct1::clear() - this = " << this << std::endl;
    #endif

        // post-ranks
        post_rank.clear();
        post_rank.shrink_to_fit();

        // pre-coords
        for (auto it = pre_coords.begin(); it != pre_coords.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        pre_coords.clear();
        pre_coords.shrink_to_fit();

        // filter
        // TODO:

    }
};

