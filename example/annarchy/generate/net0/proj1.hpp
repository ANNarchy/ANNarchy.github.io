#pragma once
#ifdef _OPENMP
    #include <omp.h>
#endif

#include "sparse_matrix.hpp"

#include "pop1.hpp"
#include "pop2.hpp"



extern PopStruct1 pop1;
extern PopStruct2 pop2;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj1: pop1 -> Custom BOLD model with target I_CBF
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct1 : LILInvMatrix<int, int> {
    ProjStruct1() : LILInvMatrix<int, int>( 1, 100) {
    }


    void init_from_lil( std::vector<int> &row_indices,
                        std::vector< std::vector<int> > &column_indices,
                        std::vector< std::vector<double> > &values,
                        std::vector< std::vector<int> > &delays) {
        static_cast<LILInvMatrix<int, int>*>(this)->init_matrix_from_lil(row_indices, column_indices);

        w = values[0][0];


    #ifdef _DEBUG_CONN
        static_cast<LILInvMatrix<int, int>*>(this)->print_data_representation();
    #endif
    }





    // Transmission and plasticity flags
    bool _transmission, _plasticity, _update;
    int _update_period;
    long int _update_offset;





    // Global parameter w
    double  w ;


    std::vector<std::vector<double>> baseline;
    std::vector<double> baseline_mean;
    std::vector<double> baseline_std;
    long time_for_init_baseline;
    int init_baseline_period;
    void start(int baseline_period) {
        init_baseline_period=baseline_period;
        time_for_init_baseline = t + baseline_period;
    #ifdef _DEBUG
        std::cout << "ProjStruct1: set new baseline period from step " << t << " to step " << time_for_init_baseline << std::endl;
    #endif
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





        time_for_init_baseline = -1;
        init_baseline_period=1;
        baseline = std::vector<std::vector<double>>(post_rank.size(), std::vector<double>() );
        baseline_mean = std::vector<double>(post_rank.size(), 0);
        baseline_std = std::vector<double>(post_rank.size(), 1);


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


        bool compute_baseline = (t < time_for_init_baseline) ? true : false;
        bool compute_average = (t == time_for_init_baseline) ? true : false;

        for(int post_idx = 0; post_idx < post_rank.size(); post_idx++) {
            double lsum = 0.0;

            // accumulate the input variable
            auto it = pre_rank[post_idx].begin();
            int j = 0;
            for(; it != pre_rank[post_idx].end(); it++, j++) {
                lsum += pop1.r[*it];
            }

            // we want to use the average across incoming connections
            // ( i. e. the recorded population )
            lsum /= static_cast<double>(pre_rank[post_idx].size());

            // if the init time is over compute the mean/standard
            // deviation across time
            if (compute_average) {
                double sum = std::accumulate(std::begin(baseline[post_idx]), std::end(baseline[post_idx]), static_cast<double>(0.0));
                baseline_mean[post_idx] = sum / static_cast<double>(baseline[post_idx].size());

                double accum = 0.0;
                std::for_each (baseline[post_idx].begin(), baseline[post_idx].end(), [&](const double value) {
                    accum += (value - baseline_mean[post_idx]) * (value - baseline_mean[post_idx]);
                });
                baseline_std[post_idx] = sqrt(accum / static_cast<double>(baseline[post_idx].size()-1));
            }

            // until init time is reached we store the rescaled sum,
            // otherwise we use the baseline mean and standard deviation to rescale
            if (compute_baseline) {
                // enqueue the value to baseline vector
                baseline[post_idx].push_back(lsum);

                // don't store the result
                pop2._sum_I_CBF[post_rank[post_idx]] += 0.0;
            } else {
                // apply relative deviation normalization
                lsum = ((lsum - baseline_mean[post_idx]) / (std::abs(baseline_mean[post_idx]) + 0.0000001));

                // store the result
                pop2._sum_I_CBF[post_rank[post_idx]] += 0.5 * lsum;
            }
        }

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

