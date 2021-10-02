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
// Main Structure for the population of id 2 (Custom BOLD model)
///////////////////////////////////////////////////////////////
struct PopStruct2{

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

    // Local parameter phi
    std::vector< double > phi;

    // Local parameter kappa
    std::vector< double > kappa;

    // Local parameter gamma
    std::vector< double > gamma;

    // Local parameter E_0
    std::vector< double > E_0;

    // Local parameter tau
    std::vector< double > tau;

    // Local parameter alpha
    std::vector< double > alpha;

    // Local parameter V_0
    std::vector< double > V_0;

    // Local parameter v_0
    std::vector< double > v_0;

    // Local parameter TE
    std::vector< double > TE;

    // Local parameter epsilon
    std::vector< double > epsilon;

    // Local parameter r_0
    std::vector< double > r_0;

    // Local parameter second
    std::vector< double > second;

    // Local parameter M
    std::vector< double > M;

    // Local parameter alpha2
    std::vector< double > alpha2;

    // Local parameter beta
    std::vector< double > beta;

    // Local variable I_CBF
    std::vector< double > I_CBF;

    // Local variable s
    std::vector< double > s;

    // Local variable f_in
    std::vector< double > f_in;

    // Local variable E
    std::vector< double > E;

    // Local variable q
    std::vector< double > q;

    // Local variable v
    std::vector< double > v;

    // Local variable f_out
    std::vector< double > f_out;

    // Local variable k_1
    std::vector< double > k_1;

    // Local variable k_2
    std::vector< double > k_2;

    // Local variable k_3
    std::vector< double > k_3;

    // Local variable BOLD
    std::vector< double > BOLD;

    // Local variable r
    std::vector< double > r;

    // Local variable BOLD_Davis
    std::vector< double > BOLD_Davis;

    // Local psp _sum_I_CBF
    std::vector< double > _sum_I_CBF;

    // Random numbers





    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter phi
        if ( name.compare("phi") == 0 ) {
            return phi;
        }

        // Local parameter kappa
        if ( name.compare("kappa") == 0 ) {
            return kappa;
        }

        // Local parameter gamma
        if ( name.compare("gamma") == 0 ) {
            return gamma;
        }

        // Local parameter E_0
        if ( name.compare("E_0") == 0 ) {
            return E_0;
        }

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau;
        }

        // Local parameter alpha
        if ( name.compare("alpha") == 0 ) {
            return alpha;
        }

        // Local parameter V_0
        if ( name.compare("V_0") == 0 ) {
            return V_0;
        }

        // Local parameter v_0
        if ( name.compare("v_0") == 0 ) {
            return v_0;
        }

        // Local parameter TE
        if ( name.compare("TE") == 0 ) {
            return TE;
        }

        // Local parameter epsilon
        if ( name.compare("epsilon") == 0 ) {
            return epsilon;
        }

        // Local parameter r_0
        if ( name.compare("r_0") == 0 ) {
            return r_0;
        }

        // Local parameter second
        if ( name.compare("second") == 0 ) {
            return second;
        }

        // Local parameter M
        if ( name.compare("M") == 0 ) {
            return M;
        }

        // Local parameter alpha2
        if ( name.compare("alpha2") == 0 ) {
            return alpha2;
        }

        // Local parameter beta
        if ( name.compare("beta") == 0 ) {
            return beta;
        }

        // Local variable I_CBF
        if ( name.compare("I_CBF") == 0 ) {
            return I_CBF;
        }

        // Local variable s
        if ( name.compare("s") == 0 ) {
            return s;
        }

        // Local variable f_in
        if ( name.compare("f_in") == 0 ) {
            return f_in;
        }

        // Local variable E
        if ( name.compare("E") == 0 ) {
            return E;
        }

        // Local variable q
        if ( name.compare("q") == 0 ) {
            return q;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v;
        }

        // Local variable f_out
        if ( name.compare("f_out") == 0 ) {
            return f_out;
        }

        // Local variable k_1
        if ( name.compare("k_1") == 0 ) {
            return k_1;
        }

        // Local variable k_2
        if ( name.compare("k_2") == 0 ) {
            return k_2;
        }

        // Local variable k_3
        if ( name.compare("k_3") == 0 ) {
            return k_3;
        }

        // Local variable BOLD
        if ( name.compare("BOLD") == 0 ) {
            return BOLD;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r;
        }

        // Local variable BOLD_Davis
        if ( name.compare("BOLD_Davis") == 0 ) {
            return BOLD_Davis;
        }

        // Local psp _sum_I_CBF
        if ( name.compare("_sum_I_CBF") == 0 ) {
            return _sum_I_CBF;
        }


        // should not happen
        std::cerr << "PopStruct2::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter phi
        if ( name.compare("phi") == 0 ) {
            return phi[rk];
        }

        // Local parameter kappa
        if ( name.compare("kappa") == 0 ) {
            return kappa[rk];
        }

        // Local parameter gamma
        if ( name.compare("gamma") == 0 ) {
            return gamma[rk];
        }

        // Local parameter E_0
        if ( name.compare("E_0") == 0 ) {
            return E_0[rk];
        }

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau[rk];
        }

        // Local parameter alpha
        if ( name.compare("alpha") == 0 ) {
            return alpha[rk];
        }

        // Local parameter V_0
        if ( name.compare("V_0") == 0 ) {
            return V_0[rk];
        }

        // Local parameter v_0
        if ( name.compare("v_0") == 0 ) {
            return v_0[rk];
        }

        // Local parameter TE
        if ( name.compare("TE") == 0 ) {
            return TE[rk];
        }

        // Local parameter epsilon
        if ( name.compare("epsilon") == 0 ) {
            return epsilon[rk];
        }

        // Local parameter r_0
        if ( name.compare("r_0") == 0 ) {
            return r_0[rk];
        }

        // Local parameter second
        if ( name.compare("second") == 0 ) {
            return second[rk];
        }

        // Local parameter M
        if ( name.compare("M") == 0 ) {
            return M[rk];
        }

        // Local parameter alpha2
        if ( name.compare("alpha2") == 0 ) {
            return alpha2[rk];
        }

        // Local parameter beta
        if ( name.compare("beta") == 0 ) {
            return beta[rk];
        }

        // Local variable I_CBF
        if ( name.compare("I_CBF") == 0 ) {
            return I_CBF[rk];
        }

        // Local variable s
        if ( name.compare("s") == 0 ) {
            return s[rk];
        }

        // Local variable f_in
        if ( name.compare("f_in") == 0 ) {
            return f_in[rk];
        }

        // Local variable E
        if ( name.compare("E") == 0 ) {
            return E[rk];
        }

        // Local variable q
        if ( name.compare("q") == 0 ) {
            return q[rk];
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            return v[rk];
        }

        // Local variable f_out
        if ( name.compare("f_out") == 0 ) {
            return f_out[rk];
        }

        // Local variable k_1
        if ( name.compare("k_1") == 0 ) {
            return k_1[rk];
        }

        // Local variable k_2
        if ( name.compare("k_2") == 0 ) {
            return k_2[rk];
        }

        // Local variable k_3
        if ( name.compare("k_3") == 0 ) {
            return k_3[rk];
        }

        // Local variable BOLD
        if ( name.compare("BOLD") == 0 ) {
            return BOLD[rk];
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }

        // Local variable BOLD_Davis
        if ( name.compare("BOLD_Davis") == 0 ) {
            return BOLD_Davis[rk];
        }

        // Local psp _sum_I_CBF
        if ( name.compare("_sum_I_CBF") == 0 ) {
            return _sum_I_CBF[rk];
        }


        // should not happen
        std::cerr << "PopStruct2::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter phi
        if ( name.compare("phi") == 0 ) {
            phi = value;
            return;
        }

        // Local parameter kappa
        if ( name.compare("kappa") == 0 ) {
            kappa = value;
            return;
        }

        // Local parameter gamma
        if ( name.compare("gamma") == 0 ) {
            gamma = value;
            return;
        }

        // Local parameter E_0
        if ( name.compare("E_0") == 0 ) {
            E_0 = value;
            return;
        }

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau = value;
            return;
        }

        // Local parameter alpha
        if ( name.compare("alpha") == 0 ) {
            alpha = value;
            return;
        }

        // Local parameter V_0
        if ( name.compare("V_0") == 0 ) {
            V_0 = value;
            return;
        }

        // Local parameter v_0
        if ( name.compare("v_0") == 0 ) {
            v_0 = value;
            return;
        }

        // Local parameter TE
        if ( name.compare("TE") == 0 ) {
            TE = value;
            return;
        }

        // Local parameter epsilon
        if ( name.compare("epsilon") == 0 ) {
            epsilon = value;
            return;
        }

        // Local parameter r_0
        if ( name.compare("r_0") == 0 ) {
            r_0 = value;
            return;
        }

        // Local parameter second
        if ( name.compare("second") == 0 ) {
            second = value;
            return;
        }

        // Local parameter M
        if ( name.compare("M") == 0 ) {
            M = value;
            return;
        }

        // Local parameter alpha2
        if ( name.compare("alpha2") == 0 ) {
            alpha2 = value;
            return;
        }

        // Local parameter beta
        if ( name.compare("beta") == 0 ) {
            beta = value;
            return;
        }

        // Local variable I_CBF
        if ( name.compare("I_CBF") == 0 ) {
            I_CBF = value;
            return;
        }

        // Local variable s
        if ( name.compare("s") == 0 ) {
            s = value;
            return;
        }

        // Local variable f_in
        if ( name.compare("f_in") == 0 ) {
            f_in = value;
            return;
        }

        // Local variable E
        if ( name.compare("E") == 0 ) {
            E = value;
            return;
        }

        // Local variable q
        if ( name.compare("q") == 0 ) {
            q = value;
            return;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v = value;
            return;
        }

        // Local variable f_out
        if ( name.compare("f_out") == 0 ) {
            f_out = value;
            return;
        }

        // Local variable k_1
        if ( name.compare("k_1") == 0 ) {
            k_1 = value;
            return;
        }

        // Local variable k_2
        if ( name.compare("k_2") == 0 ) {
            k_2 = value;
            return;
        }

        // Local variable k_3
        if ( name.compare("k_3") == 0 ) {
            k_3 = value;
            return;
        }

        // Local variable BOLD
        if ( name.compare("BOLD") == 0 ) {
            BOLD = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }

        // Local variable BOLD_Davis
        if ( name.compare("BOLD_Davis") == 0 ) {
            BOLD_Davis = value;
            return;
        }

        // Local psp _sum_I_CBF
        if ( name.compare("_sum_I_CBF") == 0 ) {
            _sum_I_CBF = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct2::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter phi
        if ( name.compare("phi") == 0 ) {
            phi[rk] = value;
            return;
        }

        // Local parameter kappa
        if ( name.compare("kappa") == 0 ) {
            kappa[rk] = value;
            return;
        }

        // Local parameter gamma
        if ( name.compare("gamma") == 0 ) {
            gamma[rk] = value;
            return;
        }

        // Local parameter E_0
        if ( name.compare("E_0") == 0 ) {
            E_0[rk] = value;
            return;
        }

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau[rk] = value;
            return;
        }

        // Local parameter alpha
        if ( name.compare("alpha") == 0 ) {
            alpha[rk] = value;
            return;
        }

        // Local parameter V_0
        if ( name.compare("V_0") == 0 ) {
            V_0[rk] = value;
            return;
        }

        // Local parameter v_0
        if ( name.compare("v_0") == 0 ) {
            v_0[rk] = value;
            return;
        }

        // Local parameter TE
        if ( name.compare("TE") == 0 ) {
            TE[rk] = value;
            return;
        }

        // Local parameter epsilon
        if ( name.compare("epsilon") == 0 ) {
            epsilon[rk] = value;
            return;
        }

        // Local parameter r_0
        if ( name.compare("r_0") == 0 ) {
            r_0[rk] = value;
            return;
        }

        // Local parameter second
        if ( name.compare("second") == 0 ) {
            second[rk] = value;
            return;
        }

        // Local parameter M
        if ( name.compare("M") == 0 ) {
            M[rk] = value;
            return;
        }

        // Local parameter alpha2
        if ( name.compare("alpha2") == 0 ) {
            alpha2[rk] = value;
            return;
        }

        // Local parameter beta
        if ( name.compare("beta") == 0 ) {
            beta[rk] = value;
            return;
        }

        // Local variable I_CBF
        if ( name.compare("I_CBF") == 0 ) {
            I_CBF[rk] = value;
            return;
        }

        // Local variable s
        if ( name.compare("s") == 0 ) {
            s[rk] = value;
            return;
        }

        // Local variable f_in
        if ( name.compare("f_in") == 0 ) {
            f_in[rk] = value;
            return;
        }

        // Local variable E
        if ( name.compare("E") == 0 ) {
            E[rk] = value;
            return;
        }

        // Local variable q
        if ( name.compare("q") == 0 ) {
            q[rk] = value;
            return;
        }

        // Local variable v
        if ( name.compare("v") == 0 ) {
            v[rk] = value;
            return;
        }

        // Local variable f_out
        if ( name.compare("f_out") == 0 ) {
            f_out[rk] = value;
            return;
        }

        // Local variable k_1
        if ( name.compare("k_1") == 0 ) {
            k_1[rk] = value;
            return;
        }

        // Local variable k_2
        if ( name.compare("k_2") == 0 ) {
            k_2[rk] = value;
            return;
        }

        // Local variable k_3
        if ( name.compare("k_3") == 0 ) {
            k_3[rk] = value;
            return;
        }

        // Local variable BOLD
        if ( name.compare("BOLD") == 0 ) {
            BOLD[rk] = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }

        // Local variable BOLD_Davis
        if ( name.compare("BOLD_Davis") == 0 ) {
            BOLD_Davis[rk] = value;
            return;
        }

        // Local psp _sum_I_CBF
        if ( name.compare("_sum_I_CBF") == 0 ) {
            _sum_I_CBF[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct2::set_local_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct2::init_population() - this = " << this << std::endl;
    #endif
        _active = true;

        // Local parameter phi
        phi = std::vector<double>(size, 0.0);

        // Local parameter kappa
        kappa = std::vector<double>(size, 0.0);

        // Local parameter gamma
        gamma = std::vector<double>(size, 0.0);

        // Local parameter E_0
        E_0 = std::vector<double>(size, 0.0);

        // Local parameter tau
        tau = std::vector<double>(size, 0.0);

        // Local parameter alpha
        alpha = std::vector<double>(size, 0.0);

        // Local parameter V_0
        V_0 = std::vector<double>(size, 0.0);

        // Local parameter v_0
        v_0 = std::vector<double>(size, 0.0);

        // Local parameter TE
        TE = std::vector<double>(size, 0.0);

        // Local parameter epsilon
        epsilon = std::vector<double>(size, 0.0);

        // Local parameter r_0
        r_0 = std::vector<double>(size, 0.0);

        // Local parameter second
        second = std::vector<double>(size, 0.0);

        // Local parameter M
        M = std::vector<double>(size, 0.0);

        // Local parameter alpha2
        alpha2 = std::vector<double>(size, 0.0);

        // Local parameter beta
        beta = std::vector<double>(size, 0.0);

        // Local variable I_CBF
        I_CBF = std::vector<double>(size, 0.0);

        // Local variable s
        s = std::vector<double>(size, 0.0);

        // Local variable f_in
        f_in = std::vector<double>(size, 0.0);

        // Local variable E
        E = std::vector<double>(size, 0.0);

        // Local variable q
        q = std::vector<double>(size, 0.0);

        // Local variable v
        v = std::vector<double>(size, 0.0);

        // Local variable f_out
        f_out = std::vector<double>(size, 0.0);

        // Local variable k_1
        k_1 = std::vector<double>(size, 0.0);

        // Local variable k_2
        k_2 = std::vector<double>(size, 0.0);

        // Local variable k_3
        k_3 = std::vector<double>(size, 0.0);

        // Local variable BOLD
        BOLD = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);

        // Local variable BOLD_Davis
        BOLD_Davis = std::vector<double>(size, 0.0);

        // Local psp _sum_I_CBF
        _sum_I_CBF = std::vector<double>(size, 0.0);






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
    std::cout << "    PopStruct2::update_rng()" << std::endl;
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
        #ifdef _TRACE_SIMULATION_STEPS
            std::cout << "    PopStruct2::update()" << std::endl;
        #endif

            // Updating the local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // I_CBF          = sum(I_CBF)
                I_CBF[i] = _sum_I_CBF[i];


                // ds/dt          = (phi * I_CBF - kappa * s - gamma * (f_in - 1))/second
                double _s = (I_CBF[i]*phi[i] - f_in[i]*gamma[i] + gamma[i] - kappa[i]*s[i])/second[i];

                // df_in/dt       = s / second
                double _f_in = s[i]/second[i];

                // ds/dt          = (phi * I_CBF - kappa * s - gamma * (f_in - 1))/second
                s[i] += dt*_s ;


                // df_in/dt       = s / second
                f_in[i] += dt*_f_in ;
                if(f_in[i] < 0.01)
                    f_in[i] = 0.01;


                // E              = 1 - (1 - E_0)**(1 / f_in)
                E[i] = 1 - pow(1 - E_0[i], 1/f_in[i]);


                // dq/dt          = (f_in * E / E_0 - (q / v) * f_out)/(tau*second)
                double _q = (E[i]*f_in[i]*v[i] - E_0[i]*f_out[i]*q[i])/(E_0[i]*second[i]*tau[i]*v[i]);

                // dv/dt          = (f_in - f_out)/(tau*second)
                double _v = (f_in[i] - f_out[i])/(second[i]*tau[i]);

                // dq/dt          = (f_in * E / E_0 - (q / v) * f_out)/(tau*second)
                q[i] += dt*_q ;
                if(q[i] < 0.01)
                    q[i] = 0.01;


                // dv/dt          = (f_in - f_out)/(tau*second)
                v[i] += dt*_v ;
                if(v[i] < 0.01)
                    v[i] = 0.01;


                // f_out          = v**(1 / alpha)
                f_out[i] = pow(v[i], 1/alpha[i]);
                if(f_out[i] < 0.01)
                    f_out[i] = 0.01;


                // k_1            = 4.3 * v_0 * E_0 * TE
                k_1[i] = 4.2999999999999998*E_0[i]*TE[i]*v_0[i];


                // k_2            = epsilon * r_0 * E_0 * TE
                k_2[i] = E_0[i]*TE[i]*epsilon[i]*r_0[i];


                // k_3            = 1.0 - epsilon
                k_3[i] = 1.0 - epsilon[i];


                // BOLD           = V_0 * (k_1 * (1 - q) + k_2 * (1 - (q / v)) + k_3 * (1 - v))
                BOLD[i] = V_0[i]*(k_1[i]*(1 - q[i]) + k_2[i]*(1 - q[i]/v[i]) + k_3[i]*(1 - v[i]));


                // r = f_in * E / E_0
                r[i] = E[i]*f_in[i]/E_0[i];
                if(r[i] < 0.01)
                    r[i] = 0.01;


                // BOLD_Davis =  M * (1 - f_in**alpha2 * (r / f_in)**beta)
                BOLD_Davis[i] = M[i]*(1 - pow(f_in[i], alpha2[i])*pow(r[i]/f_in[i], beta[i]));


            }
        } // active

    }

    void spike_gather() {

    }



    // Memory management: track the memory consumption
    long int size_in_bytes() {
        long int size_in_bytes = 0;
        // Parameters
        size_in_bytes += sizeof(double) * phi.capacity();	// phi
        size_in_bytes += sizeof(double) * kappa.capacity();	// kappa
        size_in_bytes += sizeof(double) * gamma.capacity();	// gamma
        size_in_bytes += sizeof(double) * E_0.capacity();	// E_0
        size_in_bytes += sizeof(double) * tau.capacity();	// tau
        size_in_bytes += sizeof(double) * alpha.capacity();	// alpha
        size_in_bytes += sizeof(double) * V_0.capacity();	// V_0
        size_in_bytes += sizeof(double) * v_0.capacity();	// v_0
        size_in_bytes += sizeof(double) * TE.capacity();	// TE
        size_in_bytes += sizeof(double) * epsilon.capacity();	// epsilon
        size_in_bytes += sizeof(double) * r_0.capacity();	// r_0
        size_in_bytes += sizeof(double) * second.capacity();	// second
        size_in_bytes += sizeof(double) * M.capacity();	// M
        size_in_bytes += sizeof(double) * alpha2.capacity();	// alpha2
        size_in_bytes += sizeof(double) * beta.capacity();	// beta
        // Variables
        size_in_bytes += sizeof(double) * I_CBF.capacity();	// I_CBF
        size_in_bytes += sizeof(double) * s.capacity();	// s
        size_in_bytes += sizeof(double) * f_in.capacity();	// f_in
        size_in_bytes += sizeof(double) * E.capacity();	// E
        size_in_bytes += sizeof(double) * q.capacity();	// q
        size_in_bytes += sizeof(double) * v.capacity();	// v
        size_in_bytes += sizeof(double) * f_out.capacity();	// f_out
        size_in_bytes += sizeof(double) * k_1.capacity();	// k_1
        size_in_bytes += sizeof(double) * k_2.capacity();	// k_2
        size_in_bytes += sizeof(double) * k_3.capacity();	// k_3
        size_in_bytes += sizeof(double) * BOLD.capacity();	// BOLD
        size_in_bytes += sizeof(double) * r.capacity();	// r
        size_in_bytes += sizeof(double) * BOLD_Davis.capacity();	// BOLD_Davis

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct2::clear() - this = " << this << std::endl;
#endif
        // Variables
        I_CBF.clear();
        I_CBF.shrink_to_fit();
        s.clear();
        s.shrink_to_fit();
        f_in.clear();
        f_in.shrink_to_fit();
        E.clear();
        E.shrink_to_fit();
        q.clear();
        q.shrink_to_fit();
        v.clear();
        v.shrink_to_fit();
        f_out.clear();
        f_out.shrink_to_fit();
        k_1.clear();
        k_1.shrink_to_fit();
        k_2.clear();
        k_2.shrink_to_fit();
        k_3.clear();
        k_3.shrink_to_fit();
        BOLD.clear();
        BOLD.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();
        BOLD_Davis.clear();
        BOLD_Davis.shrink_to_fit();

    }
};

