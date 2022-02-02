/*
 *  ANNarchy-version: 4.7.1
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
// proj3: pop0 -> pop0 with target inh
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct3 : LILInvMatrix<int, int> {
    ProjStruct3() : LILInvMatrix<int, int>( 500, 500) {
    }


    bool init_from_lil( std::vector<int> &row_indices,
                        std::vector< std::vector<int> > &column_indices,
                        std::vector< std::vector<double> > &values,
                        std::vector< std::vector<int> > &delays) {
        bool success = static_cast<LILInvMatrix<int, int>*>(this)->init_matrix_from_lil(row_indices, column_indices);
        if (!success)
            return false;


        // Local parameter w
        w = init_matrix_variable<double>(static_cast<double>(0.0));
        update_matrix_variable_all<double>(w, values);


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



    std::vector<std::vector<long> > _last_event;



    // Local parameter w
    std::vector< std::vector<double > > w;

    // Local parameter tau_rec
    std::vector< std::vector<double > > tau_rec;

    // Local parameter tau_facil
    std::vector< std::vector<double > > tau_facil;

    // Local parameter U
    std::vector< std::vector<double > > U;

    // Local variable x
    std::vector< std::vector<double > > x;

    // Local variable u
    std::vector< std::vector<double > > u;




    // Method called to allocate/initialize the variables
    bool init_attributes() {

        // Local parameter tau_rec
        tau_rec = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter tau_facil
        tau_facil = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter U
        U = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable x
        x = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable u
        u = init_matrix_variable<double>(static_cast<double>(0.0));

    _last_event = init_matrix_variable<long>(-10000);




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct3::init_projection() - this = " << this << std::endl;
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
        std::cout << "    ProjStruct3::compute_psp()" << std::endl;
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

                    // dx/dt = (1 - x)/tau_rec
                    x[i][j] = 1 + (x[i][j] - 1)*exp(dt*(_last_event[i][j] - (t-1))/(tau_rec[i][j]));

                    // du/dt = (U - u)/tau_facil
                    u[i][j] = U[i][j] + (u[i][j] - U[i][j])*exp(dt*(_last_event[i][j] - (t-1))/(tau_facil[i][j]));

                    // Update the last event for the synapse
                    _last_event[i][j] = t;

                    // Update conductance

                    pop0.g_inh[post_rank[i]] +=  u[i][j]*w[i][j]*x[i][j];

                    // Synaptic plasticity: pre-events

                    // x *= (1 - u)
                    x[i][j] *= 1 - u[i][j];

                    // u += U * (1 - u)
                    u[i][j] += U[i][j]*(1 - u[i][j]);

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
        std::cout << "    ProjStruct3::update_synapse()" << std::endl;
    #endif


    }

    // Post-synaptic events
    void post_event() {


    }

    // Variable/Parameter access methods

    std::vector<std::vector<double>> get_local_attribute_all_double(std::string name) {

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_all<double>(w);
        }

        if ( name.compare("tau_rec") == 0 ) {

            return get_matrix_variable_all<double>(tau_rec);
        }

        if ( name.compare("tau_facil") == 0 ) {

            return get_matrix_variable_all<double>(tau_facil);
        }

        if ( name.compare("U") == 0 ) {

            return get_matrix_variable_all<double>(U);
        }

        if ( name.compare("x") == 0 ) {

            return get_matrix_variable_all<double>(x);
        }

        if ( name.compare("u") == 0 ) {

            return get_matrix_variable_all<double>(u);
        }


        // should not happen
        std::cerr << "ProjStruct3::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<std::vector<double>>();
    }

    std::vector<double> get_local_attribute_row_double(std::string name, int rk_post) {

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_row<double>(w, rk_post);
        }

        if ( name.compare("tau_rec") == 0 ) {

            return get_matrix_variable_row<double>(tau_rec, rk_post);
        }

        if ( name.compare("tau_facil") == 0 ) {

            return get_matrix_variable_row<double>(tau_facil, rk_post);
        }

        if ( name.compare("U") == 0 ) {

            return get_matrix_variable_row<double>(U, rk_post);
        }

        if ( name.compare("x") == 0 ) {

            return get_matrix_variable_row<double>(x, rk_post);
        }

        if ( name.compare("u") == 0 ) {

            return get_matrix_variable_row<double>(u, rk_post);
        }


        // should not happen
        std::cerr << "ProjStruct3::get_local_attribute_row_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk_post, int rk_pre) {

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable<double>(w, rk_post, rk_pre);
        }

        if ( name.compare("tau_rec") == 0 ) {

            return get_matrix_variable<double>(tau_rec, rk_post, rk_pre);
        }

        if ( name.compare("tau_facil") == 0 ) {

            return get_matrix_variable<double>(tau_facil, rk_post, rk_pre);
        }

        if ( name.compare("U") == 0 ) {

            return get_matrix_variable<double>(U, rk_post, rk_pre);
        }

        if ( name.compare("x") == 0 ) {

            return get_matrix_variable<double>(x, rk_post, rk_pre);
        }

        if ( name.compare("u") == 0 ) {

            return get_matrix_variable<double>(u, rk_post, rk_pre);
        }


        // should not happen
        std::cerr << "ProjStruct3::get_local_attribute: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_local_attribute_all_double(std::string name, std::vector<std::vector<double>> value) {

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_all<double>(w, value);

            return;
        }

        if ( name.compare("tau_rec") == 0 ) {
            update_matrix_variable_all<double>(tau_rec, value);

            return;
        }

        if ( name.compare("tau_facil") == 0 ) {
            update_matrix_variable_all<double>(tau_facil, value);

            return;
        }

        if ( name.compare("U") == 0 ) {
            update_matrix_variable_all<double>(U, value);

            return;
        }

        if ( name.compare("x") == 0 ) {
            update_matrix_variable_all<double>(x, value);

            return;
        }

        if ( name.compare("u") == 0 ) {
            update_matrix_variable_all<double>(u, value);

            return;
        }

    }

    void set_local_attribute_row_double(std::string name, int rk_post, std::vector<double> value) {

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_row<double>(w, rk_post, value);

            return;
        }

        if ( name.compare("tau_rec") == 0 ) {
            update_matrix_variable_row<double>(tau_rec, rk_post, value);

            return;
        }

        if ( name.compare("tau_facil") == 0 ) {
            update_matrix_variable_row<double>(tau_facil, rk_post, value);

            return;
        }

        if ( name.compare("U") == 0 ) {
            update_matrix_variable_row<double>(U, rk_post, value);

            return;
        }

        if ( name.compare("x") == 0 ) {
            update_matrix_variable_row<double>(x, rk_post, value);

            return;
        }

        if ( name.compare("u") == 0 ) {
            update_matrix_variable_row<double>(u, rk_post, value);

            return;
        }

    }

    void set_local_attribute_double(std::string name, int rk_post, int rk_pre, double value) {

        if ( name.compare("w") == 0 ) {
            update_matrix_variable<double>(w, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("tau_rec") == 0 ) {
            update_matrix_variable<double>(tau_rec, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("tau_facil") == 0 ) {
            update_matrix_variable<double>(tau_facil, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("U") == 0 ) {
            update_matrix_variable<double>(U, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("x") == 0 ) {
            update_matrix_variable<double>(x, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("u") == 0 ) {
            update_matrix_variable<double>(u, rk_post, rk_pre, value);

            return;
        }

    }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += static_cast<LILInvMatrix<int, int>*>(this)->size_in_bytes();

        // Local variable x
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * x.capacity();
        for(auto it = x.cbegin(); it != x.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable u
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * u.capacity();
        for(auto it = u.cbegin(); it != u.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter w
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * w.capacity();
        for(auto it = w.cbegin(); it != w.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter tau_rec
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * tau_rec.capacity();
        for(auto it = tau_rec.cbegin(); it != tau_rec.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter tau_facil
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * tau_facil.capacity();
        for(auto it = tau_facil.cbegin(); it != tau_facil.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter U
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * U.capacity();
        for(auto it = U.cbegin(); it != U.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct3::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILInvMatrix<int, int>*>(this)->clear();

        // x
        for (auto it = x.begin(); it != x.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        x.clear();
        x.shrink_to_fit();

        // u
        for (auto it = u.begin(); it != u.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        u.clear();
        u.shrink_to_fit();

        // w
        for (auto it = w.begin(); it != w.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        w.clear();
        w.shrink_to_fit();

        // tau_rec
        for (auto it = tau_rec.begin(); it != tau_rec.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        tau_rec.clear();
        tau_rec.shrink_to_fit();

        // tau_facil
        for (auto it = tau_facil.begin(); it != tau_facil.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        tau_facil.clear();
        tau_facil.shrink_to_fit();

        // U
        for (auto it = U.begin(); it != U.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        U.clear();
        U.shrink_to_fit();

    }
};

