/*
 *  ANNarchy-version: 4.7.0
 */
#pragma once
#include "ANNarchy.h"
#include <random>


extern double dt;
extern long int t;
extern std::vector<std::mt19937> rng;


///////////////////////////////////////////////////////////////
// Main Structure for the population of id 1 (pop1)
///////////////////////////////////////////////////////////////
struct PopStruct1{

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



    // Structures for managing spikes
    std::vector<long int> last_spike;
    std::vector<int> spiked;

    // Refractory period
    std::vector<int> refractory;
    std::vector<int> refractory_remaining;
    std::vector<short int> in_ref;

    // Neuron specific parameters and variables

    // Local parameter noise
    std::vector< double > noise;

    // Local parameter a
    std::vector< double > a;

    // Local parameter b
    std::vector< double > b;

    // Local parameter c
    std::vector< double > c;

    // Local parameter d
    std::vector< double > d;

    // Local parameter v_thresh
    std::vector< double > v_thresh;

    // Local parameter i_offset
    std::vector< double > i_offset;

    // Local parameter tau_refrac
    std::vector< double > tau_refrac;

    // Local variable I
    std::vector< double > I;

    // Local variable v
    std::vector< double > v;

    // Local variable u
    std::vector< double > u;

    // Local variable r
    std::vector< double > r;

    // Local variable g_exc
    std::vector< double > g_exc;

    // Local variable g_inh
    std::vector< double > g_inh;

    // Random numbers
    std::vector<double> rand_0;
    std::normal_distribution< double > dist_rand_0;



    // Mean Firing rate
    std::vector< std::queue<long int> > _spike_history;
    long int _mean_fr_window;
    double _mean_fr_rate;
    void compute_firing_rate(double window){
        if(window>0.0){
            _mean_fr_window = int(window/dt);
            _mean_fr_rate = 1000./window;
        }
    };


    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            return noise;
        }

        // Local parameter a
        if ( name.compare("a") == 0 ) {
            return a;
        }

        // Local parameter b
        if ( name.compare("b") == 0 ) {
            return b;
        }

        // Local parameter c
        if ( name.compare("c") == 0 ) {
            return c;
        }

        // Local parameter d
        if ( name.compare("d") == 0 ) {
            return d;
        }

        // Local parameter v_thresh
        if ( name.compare("v_thresh") == 0 ) {
            return v_thresh;
        }

        // Local parameter i_offset
        if ( name.compare("i_offset") == 0 ) {
            return i_offset;
        }

        // Local parameter tau_refrac
        if ( name.compare("tau_refrac") == 0 ) {
            return tau_refrac;
        }

        // Local variable I
        if ( name.compare("I") == 0 ) {
            return I;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v;
        }

        // Local variable u
        if ( name.compare("u") == 0 ) {
            return u;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r;
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            return g_exc;
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            return g_inh;
        }


        // should not happen
        std::cerr << "PopStruct1::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            return noise[rk];
        }

        // Local parameter a
        if ( name.compare("a") == 0 ) {
            return a[rk];
        }

        // Local parameter b
        if ( name.compare("b") == 0 ) {
            return b[rk];
        }

        // Local parameter c
        if ( name.compare("c") == 0 ) {
            return c[rk];
        }

        // Local parameter d
        if ( name.compare("d") == 0 ) {
            return d[rk];
        }

        // Local parameter v_thresh
        if ( name.compare("v_thresh") == 0 ) {
            return v_thresh[rk];
        }

        // Local parameter i_offset
        if ( name.compare("i_offset") == 0 ) {
            return i_offset[rk];
        }

        // Local parameter tau_refrac
        if ( name.compare("tau_refrac") == 0 ) {
            return tau_refrac[rk];
        }

        // Local variable I
        if ( name.compare("I") == 0 ) {
            return I[rk];
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v[rk];
        }

        // Local variable u
        if ( name.compare("u") == 0 ) {
            return u[rk];
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            return g_exc[rk];
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            return g_inh[rk];
        }


        // should not happen
        std::cerr << "PopStruct1::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            noise = value;
            return;
        }

        // Local parameter a
        if ( name.compare("a") == 0 ) {
            a = value;
            return;
        }

        // Local parameter b
        if ( name.compare("b") == 0 ) {
            b = value;
            return;
        }

        // Local parameter c
        if ( name.compare("c") == 0 ) {
            c = value;
            return;
        }

        // Local parameter d
        if ( name.compare("d") == 0 ) {
            d = value;
            return;
        }

        // Local parameter v_thresh
        if ( name.compare("v_thresh") == 0 ) {
            v_thresh = value;
            return;
        }

        // Local parameter i_offset
        if ( name.compare("i_offset") == 0 ) {
            i_offset = value;
            return;
        }

        // Local parameter tau_refrac
        if ( name.compare("tau_refrac") == 0 ) {
            tau_refrac = value;
            return;
        }

        // Local variable I
        if ( name.compare("I") == 0 ) {
            I = value;
            return;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v = value;
            return;
        }

        // Local variable u
        if ( name.compare("u") == 0 ) {
            u = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            g_exc = value;
            return;
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            g_inh = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct1::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            noise[rk] = value;
            return;
        }

        // Local parameter a
        if ( name.compare("a") == 0 ) {
            a[rk] = value;
            return;
        }

        // Local parameter b
        if ( name.compare("b") == 0 ) {
            b[rk] = value;
            return;
        }

        // Local parameter c
        if ( name.compare("c") == 0 ) {
            c[rk] = value;
            return;
        }

        // Local parameter d
        if ( name.compare("d") == 0 ) {
            d[rk] = value;
            return;
        }

        // Local parameter v_thresh
        if ( name.compare("v_thresh") == 0 ) {
            v_thresh[rk] = value;
            return;
        }

        // Local parameter i_offset
        if ( name.compare("i_offset") == 0 ) {
            i_offset[rk] = value;
            return;
        }

        // Local parameter tau_refrac
        if ( name.compare("tau_refrac") == 0 ) {
            tau_refrac[rk] = value;
            return;
        }

        // Local variable I
        if ( name.compare("I") == 0 ) {
            I[rk] = value;
            return;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v[rk] = value;
            return;
        }

        // Local variable u
        if ( name.compare("u") == 0 ) {
            u[rk] = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            g_exc[rk] = value;
            return;
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            g_inh[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct1::set_local_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct1::init_population() - this = " << this << std::endl;
    #endif
        _active = true;

        // Local parameter noise
        noise = std::vector<double>(size, 0.0);

        // Local parameter a
        a = std::vector<double>(size, 0.0);

        // Local parameter b
        b = std::vector<double>(size, 0.0);

        // Local parameter c
        c = std::vector<double>(size, 0.0);

        // Local parameter d
        d = std::vector<double>(size, 0.0);

        // Local parameter v_thresh
        v_thresh = std::vector<double>(size, 0.0);

        // Local parameter i_offset
        i_offset = std::vector<double>(size, 0.0);

        // Local parameter tau_refrac
        tau_refrac = std::vector<double>(size, 0.0);

        // Local variable I
        I = std::vector<double>(size, 0.0);

        // Local variable v
        v = std::vector<double>(size, 0.0);

        // Local variable u
        u = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);

        // Local variable g_exc
        g_exc = std::vector<double>(size, 0.0);

        // Local variable g_inh
        g_inh = std::vector<double>(size, 0.0);

        rand_0 = std::vector<double>(size, 0.0);


        // Spiking variables
        spiked = std::vector<int>();
        last_spike = std::vector<long int>(size, -10000L);

        // Refractory period
        refractory_remaining = std::vector<int>(size, 0);
        in_ref = std::vector<short int>(size, 0);



        // Mean Firing Rate
        _spike_history = std::vector< std::queue<long int> >(size, std::queue<long int>());
        _mean_fr_window = 0;
        _mean_fr_rate = 1.0;


    }

    // Method called to reset the population
    void reset() {

        spiked.clear();
        spiked.shrink_to_fit();
        last_spike.clear();
        last_spike = std::vector<long int>(size, -10000L);

        // Refractory period
        refractory_remaining.clear();
        refractory_remaining = std::vector<int>(size, 0);



    }

    // Init rng dist
    void init_rng_dist() {

        dist_rand_0 = std::normal_distribution< double >(0.0, 1.0);

    }

    // Method to draw new random numbers
    void update_rng() {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "    PopStruct1::update_rng()" << std::endl;
#endif

        if (_active){

            for(int i = 0; i < size; i++) {

                rand_0[i] = dist_rand_0(rng[0]);

            }
        }

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

        if( _active ) {

            // compute which neurons are in refractory
            for(int i = 0; i < size; i++){
                in_ref[i] = (refractory_remaining[i] > 0) ? 0 : 1;
            }

            spiked.clear();

            // Updating local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // I = g_exc - g_inh + noise * Normal(0.0, 1.0) + i_offset
                if (in_ref[i]) { I[i] = g_exc[i] - g_inh[i] + i_offset[i] + noise[i]*rand_0[i]; }


                // dv/dt = 0.04 * v^2 + 5.0 * v + 140.0 - u + I
                double _v = I[i] - u[i] + 0.040000000000000001*pow(v[i], 2) + 5.0*v[i] + 140.0;

                // du/dt = a * (b*v - u)
                double _u = a[i]*(b[i]*v[i] - u[i]);

                // dv/dt = 0.04 * v^2 + 5.0 * v + 140.0 - u + I
                v[i] += dt*_v * in_ref[i];


                // du/dt = a * (b*v - u)
                u[i] += dt*_u * in_ref[i];


                // g_exc = 0.0
                if (in_ref[i]) { g_exc[i] = 0.0; }


                // g_inh = 0.0
                if (in_ref[i]) { g_inh[i] = 0.0; }


                // Decrement the refractory period
                refractory_remaining[i] -= (1 - in_ref[i]);

            }
        } // active

    }

    void spike_gather() {

        if( _active ) {
            for (int i = 0; i < size; i++) {

                // check if neuron is in refractory
                if (in_ref[i]==0)
                    continue;


                // Spike emission
                if(v[i] > v_thresh[i]){ // Condition is met
                    // Reset variables

                    v[i] = c[i];

                    u[i] += d[i];

                    // Store the spike
                    spiked.push_back(i);
                    last_spike[i] = t;

                    // Refractory period
                    refractory_remaining[i] = int(tau_refrac[i]/dt);

                    // Update the mean firing rate
                    if(_mean_fr_window> 0)
                        _spike_history[i].push(t);

                }

                // Update the mean firing rate
                if(_mean_fr_window> 0){
                    while((_spike_history[i].size() != 0)&&(_spike_history[i].front() <= t - _mean_fr_window)){
                        _spike_history[i].pop(); // Suppress spikes outside the window
                    }
                    r[i] = _mean_fr_rate * double(_spike_history[i].size());
                }



            }
        } // active

    }



    // Memory management: track the memory consumption
    long int size_in_bytes() {
        long int size_in_bytes = 0;
        // Parameters
        size_in_bytes += sizeof(double) * noise.capacity();	// noise
        size_in_bytes += sizeof(double) * a.capacity();	// a
        size_in_bytes += sizeof(double) * b.capacity();	// b
        size_in_bytes += sizeof(double) * c.capacity();	// c
        size_in_bytes += sizeof(double) * d.capacity();	// d
        size_in_bytes += sizeof(double) * v_thresh.capacity();	// v_thresh
        size_in_bytes += sizeof(double) * i_offset.capacity();	// i_offset
        size_in_bytes += sizeof(double) * tau_refrac.capacity();	// tau_refrac
        // Variables
        size_in_bytes += sizeof(double) * I.capacity();	// I
        size_in_bytes += sizeof(double) * v.capacity();	// v
        size_in_bytes += sizeof(double) * u.capacity();	// u
        size_in_bytes += sizeof(double) * r.capacity();	// r
        size_in_bytes += sizeof(double) * g_exc.capacity();	// g_exc
        size_in_bytes += sizeof(double) * g_inh.capacity();	// g_inh

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct1::clear() - this = " << this << std::endl;
#endif
        // Variables
        I.clear();
        I.shrink_to_fit();
        v.clear();
        v.shrink_to_fit();
        u.clear();
        u.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();
        g_exc.clear();
        g_exc.shrink_to_fit();
        g_inh.clear();
        g_inh.shrink_to_fit();

    }
};

