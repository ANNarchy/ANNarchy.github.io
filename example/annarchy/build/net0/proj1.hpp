/*
 *  ANNarchy-version: 4.7.1.1
 */
#pragma once

#include "ANNarchy.h"
#include "LILInvMatrix.hpp"




extern PopStruct0 pop0;
extern PopStruct0 pop0;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj1: pop0 -> pop0 with target inh
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct1 : LILInvMatrix<int, int> {
    ProjStruct1() : LILInvMatrix<int, int>( 4000, 4000) {
    }


    bool init_from_lil( std::vector<int> &row_indices,
                        std::vector< std::vector<int> > &column_indices,
                        std::vector< std::vector<double> > &values,
                        std::vector< std::vector<int> > &delays) {
        bool success = static_cast<LILInvMatrix<int, int>*>(this)->init_matrix_from_lil(row_indices, column_indices);
        if (!success)
            return false;

        w = values[0][0];


        // init other variables than 'w' or delay
        if (!init_attributes()){
            return false;
        }

    #ifdef _DEBUG_CONN
        static_cast<LILInvMatrix<int, int>*>(this)->print_data_representation();
    #endif
        return true;
    }





    // Transmission and plasticity flags
    bool _transmission, _plasticity, _update;
    int _update_period;
    long int _update_offset;





    // Global parameter w
    double  w ;




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
int nb_post; double sum;

        // Event-based summation
        if (_transmission && pop0._active){


            // Iterate over all incoming spikes (possibly delayed constantly)
            for(int _idx_j = 0; _idx_j < pop0.spiked.size(); _idx_j++){
                // Rank of the presynaptic neuron
                int rk_j = pop0.spiked[_idx_j];
                // Find the presynaptic neuron in the inverse connectivity matrix
                auto inv_post_ptr = inv_pre_rank.find(rk_j);
                if (inv_post_ptr == inv_pre_rank.end())
                    continue;
                // List of postsynaptic neurons receiving spikes from that neuron
                std::vector< std::pair<int, int> >& inv_post = inv_post_ptr->second;
                // Number of post neurons
                int nb_post = inv_post.size();

                // Iterate over connected post neurons
                for(int _idx_i = 0; _idx_i < nb_post; _idx_i++){
                    // Retrieve the correct indices
                    int i = inv_post[_idx_i].first;
                    int j = inv_post[_idx_i].second;

                    // Event-driven integration

                    // Update conductance

                    pop0.g_inh[post_rank[i]] +=  w;

                    // Synaptic plasticity: pre-events

                }
            }
        } // active

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

    double get_global_attribute_double(std::string name) {

        if ( name.compare("w") == 0 ) {
            return w;
        }


        // should not happen
        std::cerr << "ProjStruct1::get_global_attribute_double: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_global_attribute_double(std::string name, double value) {

        if ( name.compare("w") == 0 ) {
            w = value;

            return;
        }

    }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += static_cast<LILInvMatrix<int, int>*>(this)->size_in_bytes();

        // Global parameter w
        size_in_bytes += sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct1::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILInvMatrix<int, int>*>(this)->clear();

    }
};

