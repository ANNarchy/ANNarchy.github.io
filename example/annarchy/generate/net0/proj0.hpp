/*
 *  ANNarchy-version: 4.7.1
 */
#pragma once

#include "ANNarchy.h"
#include "Specific.hpp"

#include <limits>


extern PopStruct0 pop0;
extern PopStruct1 pop1;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj0: pop0 -> pop1 with target exc
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct0 : SpecificConnectivity {
    ProjStruct0() : SpecificConnectivity() {
    }




    // connectivity data
    std::vector<int> post_rank;
    std::vector< std::vector<int> > pre_rank;


    // Accessor to connectivity data
    std::vector<int> get_post_rank() { return post_rank; }
    void set_post_rank(std::vector<int> ranks) { post_rank = ranks; }
    std::vector< std::vector<int> > get_pre_rank() { return pre_rank; }
    void set_pre_rank(std::vector< std::vector<int> > ranks) { pre_rank = ranks; }
    int nb_synapses() {
        int size = 0;
        for(auto it = pre_rank.cbegin(); it != pre_rank.cend(); it++)
            size += it->size();
        return size;
    }
    int dendrite_size(int n) { return pre_rank[n].size(); }
    int nb_dendrites() { return post_rank.size(); }


    // Transmission and plasticity flags
    bool _transmission, _plasticity, _update;
    int _update_period;
    long int _update_offset;








    // Method called to allocate/initialize the variables
    bool init_attributes() {




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct0::init_projection() - this = " << this << std::endl;
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
        std::cout << "    ProjStruct0::compute_psp()" << std::endl;
    #endif

        int rk_pre;
        double sum=0.0;


        if ( _transmission && pop0._active ) {
        std::vector<int> coord;


        for(int i = 0; i < 9216; i++){
            coord = pre_rank[i];

            sum = 0.0;

            for(int i_w = 0; i_w < 10.0; i_w++){

            for(int j_w = 0; j_w < 10.0; j_w++){

                int i_pre = coord[0] + i_w;
                int j_pre = coord[1] + j_w;
                int k_pre = coord[2];
                if ((i_pre < 0) ||(i_pre > 479)){
                    continue;
                }
                if ((j_pre < 0) ||(j_pre > 639)){
                    continue;
                }
                if ((k_pre < 0) ||(k_pre > 2)){
                    continue;
                }
                rk_pre = 3*(640*(i_pre) + j_pre) + k_pre;
                sum += pop0.r[rk_pre];;
            }
            }
            pop1._sum_exc[i] += sum/100.0;
        } // for
        } // if

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct0::update_synapse()" << std::endl;
    #endif


    }

    // Post-synaptic events
    void post_event() {


    }

    // Variable/Parameter access methods


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += sizeof(std::vector<int>);
        size_in_bytes += pre_rank.capacity() * sizeof(int);

        size_in_bytes += sizeof(std::vector<std::vector<int>>);
        size_in_bytes += pre_rank.capacity() * sizeof(std::vector<int>);
        for (auto it = pre_rank.begin(); it != pre_rank.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(int);
        }

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct0::clear() - this = " << this << std::endl;
    #endif

        // post-ranks
        post_rank.clear();
        post_rank.shrink_to_fit();

        // pre-ranks sub-lists
        for (auto it = pre_rank.begin(); it != pre_rank.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        // pre-ranks top-list
        pre_rank.clear();
        pre_rank.shrink_to_fit();

    }
};

