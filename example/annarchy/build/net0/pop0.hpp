/*
 *  ANNarchy-version: 4.7.1.1
 */
#pragma once

#include "ANNarchy.h"
#include <random>



extern double dt;
extern long int t;
extern std::vector<std::mt19937> rng;


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



    // Structures for managing spikes
    std::vector<long int> last_spike;
    std::vector<int> spiked;

    // Refractory period
    std::vector<int> refractory;
    std::vector<int> refractory_remaining;
    std::vector<short int> in_ref;

    // Neuron specific parameters and variables

    // Global parameter El
    double  El ;

    // Global parameter Vr
    double  Vr ;

    // Global parameter Erev_exc
    double  Erev_exc ;

    // Global parameter Erev_inh
    double  Erev_inh ;

    // Global parameter Vt
    double  Vt ;

    // Global parameter tau
    double  tau ;

    // Global parameter tau_exc
    double  tau_exc ;

    // Global parameter tau_inh
    double  tau_inh ;

    // Global parameter I
    double  I ;

    // Local variable v
    std::vector< double > v;

    // Local variable g_exc
    std::vector< double > g_exc;

    // Local variable g_inh
    std::vector< double > g_inh;

    // Local variable r
    std::vector< double > r;

    // Random numbers



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

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v;
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            return g_exc;
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            return g_inh;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r;
        }


        // should not happen
        std::cerr << "PopStruct0::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v[rk];
        }

        // Local variable g_exc
        if ( name.compare("g_exc") == 0 ) {
            return g_exc[rk];
        }

        // Local variable g_inh
        if ( name.compare("g_inh") == 0 ) {
            return g_inh[rk];
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }


        // should not happen
        std::cerr << "PopStruct0::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v = value;
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

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct0::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v[rk] = value;
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

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct0::set_local_attribute_double: " << name << " not found" << std::endl;
    }

    double get_global_attribute_double(std::string name) {

        // Global parameter El
        if ( name.compare("El") == 0 ) {
            return El;
        }

        // Global parameter Vr
        if ( name.compare("Vr") == 0 ) {
            return Vr;
        }

        // Global parameter Erev_exc
        if ( name.compare("Erev_exc") == 0 ) {
            return Erev_exc;
        }

        // Global parameter Erev_inh
        if ( name.compare("Erev_inh") == 0 ) {
            return Erev_inh;
        }

        // Global parameter Vt
        if ( name.compare("Vt") == 0 ) {
            return Vt;
        }

        // Global parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau;
        }

        // Global parameter tau_exc
        if ( name.compare("tau_exc") == 0 ) {
            return tau_exc;
        }

        // Global parameter tau_inh
        if ( name.compare("tau_inh") == 0 ) {
            return tau_inh;
        }

        // Global parameter I
        if ( name.compare("I") == 0 ) {
            return I;
        }


        // should not happen
        std::cerr << "PopStruct0::get_global_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_global_attribute_double(std::string name, double value)  {

        // Global parameter El
        if ( name.compare("El") == 0 ) {
            El = value;
            return;
        }

        // Global parameter Vr
        if ( name.compare("Vr") == 0 ) {
            Vr = value;
            return;
        }

        // Global parameter Erev_exc
        if ( name.compare("Erev_exc") == 0 ) {
            Erev_exc = value;
            return;
        }

        // Global parameter Erev_inh
        if ( name.compare("Erev_inh") == 0 ) {
            Erev_inh = value;
            return;
        }

        // Global parameter Vt
        if ( name.compare("Vt") == 0 ) {
            Vt = value;
            return;
        }

        // Global parameter tau
        if ( name.compare("tau") == 0 ) {
            tau = value;
            return;
        }

        // Global parameter tau_exc
        if ( name.compare("tau_exc") == 0 ) {
            tau_exc = value;
            return;
        }

        // Global parameter tau_inh
        if ( name.compare("tau_inh") == 0 ) {
            tau_inh = value;
            return;
        }

        // Global parameter I
        if ( name.compare("I") == 0 ) {
            I = value;
            return;
        }


        std::cerr << "PopStruct0::set_global_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct0::init_population(size="<<this->size<<") - this = " << this << std::endl;
    #endif
        _active = true;

        // Global parameter El
        El = 0.0;

        // Global parameter Vr
        Vr = 0.0;

        // Global parameter Erev_exc
        Erev_exc = 0.0;

        // Global parameter Erev_inh
        Erev_inh = 0.0;

        // Global parameter Vt
        Vt = 0.0;

        // Global parameter tau
        tau = 0.0;

        // Global parameter tau_exc
        tau_exc = 0.0;

        // Global parameter tau_inh
        tau_inh = 0.0;

        // Global parameter I
        I = 0.0;

        // Local variable v
        v = std::vector<double>(size, 0.0);

        // Local variable g_exc
        g_exc = std::vector<double>(size, 0.0);

        // Local variable g_inh
        g_inh = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);


        // Spiking variables
        spiked = std::vector<int>();
        last_spike = std::vector<long int>(size, -10000L);

        // Refractory period
        refractory = std::vector<int>(size, 0);
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

        if( _active ) {

            // compute which neurons are in refractory
            for(int i = 0; i < size; i++){
                in_ref[i] = (refractory_remaining[i] > 0) ? 0 : 1;
            }

            spiked.clear();

            // Updating local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // tau * dv/dt = (El - v) + g_exc * (Erev_exc - v) + g_inh * (Erev_inh - v ) + I
                double _v = (El + Erev_exc*g_exc[i] + Erev_inh*g_inh[i] + I - g_exc[i]*v[i] - g_inh[i]*v[i] - v[i])/tau;

                // tau_exc * dg_exc/dt = - g_exc
                double _g_exc = -g_exc[i]/tau_exc;

                // tau_inh * dg_inh/dt = - g_inh
                double _g_inh = -g_inh[i]/tau_inh;

                // tau * dv/dt = (El - v) + g_exc * (Erev_exc - v) + g_inh * (Erev_inh - v ) + I
                v[i] += dt*_v * in_ref[i];


                // tau_exc * dg_exc/dt = - g_exc
                g_exc[i] += dt*_g_exc ;


                // tau_inh * dg_inh/dt = - g_inh
                g_inh[i] += dt*_g_inh ;


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
                if(v[i] > Vt){ // Condition is met
                    // Reset variables

                    v[i] = Vr;

                    // Store the spike
                    spiked.push_back(i);
                    last_spike[i] = t;

                    // Refractory period
                    refractory_remaining[i] = refractory[i];

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
        size_in_bytes += sizeof(double);	// El
        size_in_bytes += sizeof(double);	// Vr
        size_in_bytes += sizeof(double);	// Erev_exc
        size_in_bytes += sizeof(double);	// Erev_inh
        size_in_bytes += sizeof(double);	// Vt
        size_in_bytes += sizeof(double);	// tau
        size_in_bytes += sizeof(double);	// tau_exc
        size_in_bytes += sizeof(double);	// tau_inh
        size_in_bytes += sizeof(double);	// I
        // Variables
        size_in_bytes += sizeof(double) * v.capacity();	// v
        size_in_bytes += sizeof(double) * g_exc.capacity();	// g_exc
        size_in_bytes += sizeof(double) * g_inh.capacity();	// g_inh
        size_in_bytes += sizeof(double) * r.capacity();	// r
        // RNGs

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct0::clear() - this = " << this << std::endl;
#endif
        // Variables
        v.clear();
        v.shrink_to_fit();
        g_exc.clear();
        g_exc.shrink_to_fit();
        g_inh.clear();
        g_inh.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();

        // Mean Firing Rate
        for (auto it = _spike_history.begin(); it != _spike_history.end(); it++) {
            while(!it->empty())
                it->pop();
        }
        _spike_history.clear();
        _spike_history.shrink_to_fit();

        // RNGs

    }
};

