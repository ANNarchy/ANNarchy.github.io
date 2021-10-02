# cython: embedsignature=True
from cpython.exc cimport PyErr_CheckSignals
from libcpp.vector cimport vector
from libcpp.map cimport map, pair
from libcpp cimport bool
from libcpp.string cimport string
from math import ceil
import numpy as np
import sys
cimport numpy as np
cimport cython

# Short names for unsigned integer types
ctypedef unsigned char _ann_uint8
ctypedef unsigned short _ann_uint16
ctypedef unsigned int _ann_uint32
ctypedef unsigned long _ann_uint64

import ANNarchy
from ANNarchy.core.cython_ext.Connector cimport LILConnectivity as LIL

cdef extern from "ANNarchy.h":

    # User-defined functions


    # User-defined constants


    # Data structures

    # Export Population 0 (pop0)
    cdef struct PopStruct0 :
        # Number of neurons
        int get_size()
        void set_size(int)
        # Maximum delay in steps
        int get_max_delay()
        void set_max_delay(int)
        void update_max_delay(int)
        # Activate/deactivate the population
        bool is_active()
        void set_active(bool)
        # Reset the population
        void reset()

        vector[int] refractory


        # Local attributes
        vector[double] get_local_attribute_all_double(string)
        double get_local_attribute_double(string, int)
        void set_local_attribute_all_double(string, vector[double])
        void set_local_attribute_double(string, int, double)




        # Compute firing rate
        void compute_firing_rate(double window)


        # memory management
        long int size_in_bytes()
        void clear()

    # Export Population 1 (pop1)
    cdef struct PopStruct1 :
        # Number of neurons
        int get_size()
        void set_size(int)
        # Maximum delay in steps
        int get_max_delay()
        void set_max_delay(int)
        void update_max_delay(int)
        # Activate/deactivate the population
        bool is_active()
        void set_active(bool)
        # Reset the population
        void reset()

        vector[int] refractory


        # Local attributes
        vector[double] get_local_attribute_all_double(string)
        double get_local_attribute_double(string, int)
        void set_local_attribute_all_double(string, vector[double])
        void set_local_attribute_double(string, int, double)




        # Compute firing rate
        void compute_firing_rate(double window)


        # memory management
        long int size_in_bytes()
        void clear()

    # Export Population 2 (Custom BOLD model)
    cdef struct PopStruct2 :
        # Number of neurons
        int get_size()
        void set_size(int)
        # Maximum delay in steps
        int get_max_delay()
        void set_max_delay(int)
        void update_max_delay(int)
        # Activate/deactivate the population
        bool is_active()
        void set_active(bool)
        # Reset the population
        void reset()


        # Local attributes
        vector[double] get_local_attribute_all_double(string)
        double get_local_attribute_double(string, int)
        void set_local_attribute_all_double(string, vector[double])
        void set_local_attribute_double(string, int, double)



        # Targets
        vector[double] _sum_I_CBF



        # memory management
        long int size_in_bytes()
        void clear()


    # Export Projection 0
    cdef struct ProjStruct0 :
        # Flags
        bool _transmission
        bool _plasticity
        bool _update
        int _update_period
        long _update_offset

        # Connectivity
        void init_from_lil(vector[int], vector[vector[int]], vector[vector[double]], vector[vector[int]])
        # Access connectivity
        vector[int] get_post_rank()
        vector[ vector[int] ] get_pre_ranks()
        vector[int] get_dendrite_pre_rank(int)
        int nb_synapses()
        int nb_dendrites()
        int dendrite_size(int)

        map[int, int] nb_efferent_synapses()





        # Global Attributes
        double get_global_attribute_double(string)
        void set_global_attribute_double(string, double)




        void start(int)


        # memory management
        long int size_in_bytes()
        void clear()

    # Export Projection 1
    cdef struct ProjStruct1 :
        # Flags
        bool _transmission
        bool _plasticity
        bool _update
        int _update_period
        long _update_offset

        # Connectivity
        void init_from_lil(vector[int], vector[vector[int]], vector[vector[double]], vector[vector[int]])
        # Access connectivity
        vector[int] get_post_rank()
        vector[ vector[int] ] get_pre_ranks()
        vector[int] get_dendrite_pre_rank(int)
        int nb_synapses()
        int nb_dendrites()
        int dendrite_size(int)

        map[int, int] nb_efferent_synapses()





        # Global Attributes
        double get_global_attribute_double(string)
        void set_global_attribute_double(string, double)




        void start(int)


        # memory management
        long int size_in_bytes()
        void clear()



    # Monitors
    cdef cppclass Monitor:
        vector[int] ranks
        int period_
        int period_offset_
        long offset_


    # Population 0 (pop0) : Monitor
    cdef cppclass PopRecorder0 (Monitor):
        @staticmethod
        int create_instance(vector[int], int, int, long)
        @staticmethod
        PopRecorder0* get_instance(int)
        long int size_in_bytes()
        void clear()

        vector[vector[double]] I
        bool record_I

        vector[vector[double]] v
        bool record_v

        vector[vector[double]] u
        bool record_u

        vector[vector[double]] r
        bool record_r

        vector[vector[double]] g_exc
        bool record_g_exc

        vector[vector[double]] g_inh
        bool record_g_inh

        map[int, vector[long]] spike
        bool record_spike
        void clear_spike()

    # Population 1 (pop1) : Monitor
    cdef cppclass PopRecorder1 (Monitor):
        @staticmethod
        int create_instance(vector[int], int, int, long)
        @staticmethod
        PopRecorder1* get_instance(int)
        long int size_in_bytes()
        void clear()

        vector[vector[double]] I
        bool record_I

        vector[vector[double]] v
        bool record_v

        vector[vector[double]] u
        bool record_u

        vector[vector[double]] r
        bool record_r

        vector[vector[double]] g_exc
        bool record_g_exc

        vector[vector[double]] g_inh
        bool record_g_inh

        map[int, vector[long]] spike
        bool record_spike
        void clear_spike()

    # Population 2 (Custom BOLD model) : Monitor
    cdef cppclass PopRecorder2 (Monitor):
        @staticmethod
        int create_instance(vector[int], int, int, long)
        @staticmethod
        PopRecorder2* get_instance(int)
        long int size_in_bytes()
        void clear()

        vector[vector[double]] I_CBF
        bool record_I_CBF

        vector[vector[double]] s
        bool record_s

        vector[vector[double]] f_in
        bool record_f_in

        vector[vector[double]] E
        bool record_E

        vector[vector[double]] q
        bool record_q

        vector[vector[double]] v
        bool record_v

        vector[vector[double]] f_out
        bool record_f_out

        vector[vector[double]] k_1
        bool record_k_1

        vector[vector[double]] k_2
        bool record_k_2

        vector[vector[double]] k_3
        bool record_k_3

        vector[vector[double]] BOLD
        bool record_BOLD

        vector[vector[double]] r
        bool record_r

        vector[vector[double]] BOLD_Davis
        bool record_BOLD_Davis

        # Targets
        vector[vector[double]] _sum_I_CBF
        bool record__sum_I_CBF

    # Projection 0 : Monitor
    cdef cppclass ProjRecorder0 (Monitor):
        @staticmethod
        int create_instance(vector[int], int, int, long)
        @staticmethod
        ProjRecorder0* get_instance(int)

    # Projection 1 : Monitor
    cdef cppclass ProjRecorder1 (Monitor):
        @staticmethod
        int create_instance(vector[int], int, int, long)
        @staticmethod
        ProjRecorder1* get_instance(int)


    # Instances

    PopStruct0 pop0
    PopStruct1 pop1
    PopStruct2 pop2

    ProjStruct0 proj0
    ProjStruct1 proj1

    # Methods
    void initialize(double)
    void init_rng_dist()
    void setSeed(long, int, bool)
    void run(int nbSteps) nogil
    int run_until(int steps, vector[int] populations, bool or_and)
    void step()

    # Time
    long getTime()
    void setTime(long)

    # dt
    double getDt()
    void setDt(double dt_)


    # Number of threads
    void setNumberThreads(int, vector[int])


# Population wrappers

# Wrapper for population 0 (pop0)
@cython.auto_pickle(True)
cdef class pop0_wrapper :

    def __init__(self, size, max_delay):

        pop0.set_size(size)
        pop0.set_max_delay(max_delay)
    # Number of neurons
    property size:
        def __get__(self):
            return pop0.get_size()
    # Reset the population
    def reset(self):
        pop0.reset()
    # Set the maximum delay of outgoing projections
    def set_max_delay(self, val):
        pop0.set_max_delay(val)
    # Updates the maximum delay of outgoing projections and rebuilds the arrays
    def update_max_delay(self, val):
        pop0.update_max_delay(val)
    # Allows the population to compute
    def activate(self, bool val):
        pop0.set_active(val)


    # Local Attribute
    def get_local_attribute_all(self, name, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return np.array(pop0.get_local_attribute_all_double(cpp_string))


    def get_local_attribute(self, name, rk, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return pop0.get_local_attribute_double(cpp_string, rk)


    def set_local_attribute_all(self, name, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop0.set_local_attribute_all_double(cpp_string, value)


    def set_local_attribute(self, name, rk, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop0.set_local_attribute_double(cpp_string, rk, value)





    # Refractory period
    cpdef np.ndarray get_refractory(self):
        return np.array(pop0.refractory)
    cpdef set_refractory(self, np.ndarray value):
        pop0.refractory = value


    # Compute firing rate
    cpdef compute_firing_rate(self, double window):
        pop0.compute_firing_rate(window)


    # memory management
    def size_in_bytes(self):
        return pop0.size_in_bytes()

    def clear(self):
        return pop0.clear()

# Wrapper for population 1 (pop1)
@cython.auto_pickle(True)
cdef class pop1_wrapper :

    def __init__(self, size, max_delay):

        pop1.set_size(size)
        pop1.set_max_delay(max_delay)
    # Number of neurons
    property size:
        def __get__(self):
            return pop1.get_size()
    # Reset the population
    def reset(self):
        pop1.reset()
    # Set the maximum delay of outgoing projections
    def set_max_delay(self, val):
        pop1.set_max_delay(val)
    # Updates the maximum delay of outgoing projections and rebuilds the arrays
    def update_max_delay(self, val):
        pop1.update_max_delay(val)
    # Allows the population to compute
    def activate(self, bool val):
        pop1.set_active(val)


    # Local Attribute
    def get_local_attribute_all(self, name, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return np.array(pop1.get_local_attribute_all_double(cpp_string))


    def get_local_attribute(self, name, rk, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return pop1.get_local_attribute_double(cpp_string, rk)


    def set_local_attribute_all(self, name, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop1.set_local_attribute_all_double(cpp_string, value)


    def set_local_attribute(self, name, rk, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop1.set_local_attribute_double(cpp_string, rk, value)





    # Refractory period
    cpdef np.ndarray get_refractory(self):
        return np.array(pop1.refractory)
    cpdef set_refractory(self, np.ndarray value):
        pop1.refractory = value


    # Compute firing rate
    cpdef compute_firing_rate(self, double window):
        pop1.compute_firing_rate(window)


    # memory management
    def size_in_bytes(self):
        return pop1.size_in_bytes()

    def clear(self):
        return pop1.clear()

# Wrapper for population 2 (Custom BOLD model)
@cython.auto_pickle(True)
cdef class pop2_wrapper :

    def __init__(self, size, max_delay):

        pop2.set_size(size)
        pop2.set_max_delay(max_delay)
    # Number of neurons
    property size:
        def __get__(self):
            return pop2.get_size()
    # Reset the population
    def reset(self):
        pop2.reset()
    # Set the maximum delay of outgoing projections
    def set_max_delay(self, val):
        pop2.set_max_delay(val)
    # Updates the maximum delay of outgoing projections and rebuilds the arrays
    def update_max_delay(self, val):
        pop2.update_max_delay(val)
    # Allows the population to compute
    def activate(self, bool val):
        pop2.set_active(val)


    # Local Attribute
    def get_local_attribute_all(self, name, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return np.array(pop2.get_local_attribute_all_double(cpp_string))


    def get_local_attribute(self, name, rk, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            return pop2.get_local_attribute_double(cpp_string, rk)


    def set_local_attribute_all(self, name, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop2.set_local_attribute_all_double(cpp_string, value)


    def set_local_attribute(self, name, rk, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":
            pop2.set_local_attribute_double(cpp_string, rk, value)



    # Targets
    cpdef np.ndarray get_sum_I_CBF(self):
        return np.array(pop2.get_local_attribute_all_double("_sum_I_CBF".encode('utf-8')))





    # memory management
    def size_in_bytes(self):
        return pop2.size_in_bytes()

    def clear(self):
        return pop2.clear()


# Projection wrappers

# Wrapper for projection 0
@cython.auto_pickle(True)
cdef class proj0_wrapper :

    def __init__(self, ):
                    pass


    def init_from_lil(self, synapses):
        proj0.init_from_lil(synapses.post_rank, synapses.pre_rank, synapses.w, synapses.delay)


    property size:
        def __get__(self):
            return proj0.nb_dendrites()

    # Transmission flag
    def _get_transmission(self):
        return proj0._transmission
    def _set_transmission(self, bool l):
        proj0._transmission = l

    # Update flag
    def _get_update(self):
        return proj0._update
    def _set_update(self, bool l):
        proj0._update = l

    # Plasticity flag
    def _get_plasticity(self):
        return proj0._plasticity
    def _set_plasticity(self, bool l):
        proj0._plasticity = l

    # Update period
    def _get_update_period(self):
        return proj0._update_period
    def _set_update_period(self, int l):
        proj0._update_period = l

    # Update offset
    def _get_update_offset(self):
        return proj0._update_offset
    def _set_update_offset(self, long l):
        proj0._update_offset = l

    # Access connectivity

    def post_rank(self):
        return proj0.get_post_rank()
    def pre_rank_all(self):
        return proj0.get_pre_ranks()
    def pre_rank(self, int n):
        return proj0.get_dendrite_pre_rank(n)
    def nb_dendrites(self):
        return proj0.nb_dendrites()
    def nb_synapses(self):
        return proj0.nb_synapses()
    def dendrite_size(self, int n):
        return proj0.dendrite_size(n)

    def nb_efferent_synapses(self):
        return proj0.nb_efferent_synapses()




    # Global Attributes
    def get_global_attribute(self, name, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":            
            return proj0.get_global_attribute_double(cpp_string)


    def set_global_attribute(self, name, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":            
            proj0.set_global_attribute_double(cpp_string, value)





    def start(self, baseline_period):
        proj0.start(baseline_period)


    # memory management
    def size_in_bytes(self):
        return proj0.size_in_bytes()

    def clear(self):
        return proj0.clear()

# Wrapper for projection 1
@cython.auto_pickle(True)
cdef class proj1_wrapper :

    def __init__(self, ):
                    pass


    def init_from_lil(self, synapses):
        proj1.init_from_lil(synapses.post_rank, synapses.pre_rank, synapses.w, synapses.delay)


    property size:
        def __get__(self):
            return proj1.nb_dendrites()

    # Transmission flag
    def _get_transmission(self):
        return proj1._transmission
    def _set_transmission(self, bool l):
        proj1._transmission = l

    # Update flag
    def _get_update(self):
        return proj1._update
    def _set_update(self, bool l):
        proj1._update = l

    # Plasticity flag
    def _get_plasticity(self):
        return proj1._plasticity
    def _set_plasticity(self, bool l):
        proj1._plasticity = l

    # Update period
    def _get_update_period(self):
        return proj1._update_period
    def _set_update_period(self, int l):
        proj1._update_period = l

    # Update offset
    def _get_update_offset(self):
        return proj1._update_offset
    def _set_update_offset(self, long l):
        proj1._update_offset = l

    # Access connectivity

    def post_rank(self):
        return proj1.get_post_rank()
    def pre_rank_all(self):
        return proj1.get_pre_ranks()
    def pre_rank(self, int n):
        return proj1.get_dendrite_pre_rank(n)
    def nb_dendrites(self):
        return proj1.nb_dendrites()
    def nb_synapses(self):
        return proj1.nb_synapses()
    def dendrite_size(self, int n):
        return proj1.dendrite_size(n)

    def nb_efferent_synapses(self):
        return proj1.nb_efferent_synapses()




    # Global Attributes
    def get_global_attribute(self, name, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":            
            return proj1.get_global_attribute_double(cpp_string)


    def set_global_attribute(self, name, value, ctype):
        cpp_string = name.encode('utf-8')

        if ctype == "double":            
            proj1.set_global_attribute_double(cpp_string, value)





    def start(self, baseline_period):
        proj1.start(baseline_period)


    # memory management
    def size_in_bytes(self):
        return proj1.size_in_bytes()

    def clear(self):
        return proj1.clear()


# Monitor wrappers

# Population Monitor wrapper
@cython.auto_pickle(True)
cdef class PopRecorder0_wrapper:
    cdef int id
    def __init__(self, list ranks, int period, period_offset, long offset):
        self.id = PopRecorder0.create_instance(ranks, period, period_offset, offset)

    def size_in_bytes(self):
        return (PopRecorder0.get_instance(self.id)).size_in_bytes()

    def clear(self):
        return (PopRecorder0.get_instance(self.id)).clear()

    property I:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).I
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).I = val
    property record_I:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_I
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_I = val
    def clear_I(self):
        (PopRecorder0.get_instance(self.id)).I.clear()

    property v:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).v
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).v = val
    property record_v:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_v
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_v = val
    def clear_v(self):
        (PopRecorder0.get_instance(self.id)).v.clear()

    property u:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).u
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).u = val
    property record_u:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_u
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_u = val
    def clear_u(self):
        (PopRecorder0.get_instance(self.id)).u.clear()

    property r:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).r
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).r = val
    property record_r:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_r
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_r = val
    def clear_r(self):
        (PopRecorder0.get_instance(self.id)).r.clear()

    property g_exc:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).g_exc
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).g_exc = val
    property record_g_exc:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_g_exc
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_g_exc = val
    def clear_g_exc(self):
        (PopRecorder0.get_instance(self.id)).g_exc.clear()

    property g_inh:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).g_inh
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).g_inh = val
    property record_g_inh:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_g_inh
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_g_inh = val
    def clear_g_inh(self):
        (PopRecorder0.get_instance(self.id)).g_inh.clear()

    property spike:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).spike
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).spike = val
    property record_spike:
        def __get__(self): return (PopRecorder0.get_instance(self.id)).record_spike
        def __set__(self, val): (PopRecorder0.get_instance(self.id)).record_spike = val
    def clear_spike(self):
        (PopRecorder0.get_instance(self.id)).clear_spike()

# Population Monitor wrapper
@cython.auto_pickle(True)
cdef class PopRecorder1_wrapper:
    cdef int id
    def __init__(self, list ranks, int period, period_offset, long offset):
        self.id = PopRecorder1.create_instance(ranks, period, period_offset, offset)

    def size_in_bytes(self):
        return (PopRecorder1.get_instance(self.id)).size_in_bytes()

    def clear(self):
        return (PopRecorder1.get_instance(self.id)).clear()

    property I:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).I
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).I = val
    property record_I:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_I
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_I = val
    def clear_I(self):
        (PopRecorder1.get_instance(self.id)).I.clear()

    property v:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).v
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).v = val
    property record_v:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_v
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_v = val
    def clear_v(self):
        (PopRecorder1.get_instance(self.id)).v.clear()

    property u:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).u
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).u = val
    property record_u:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_u
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_u = val
    def clear_u(self):
        (PopRecorder1.get_instance(self.id)).u.clear()

    property r:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).r
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).r = val
    property record_r:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_r
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_r = val
    def clear_r(self):
        (PopRecorder1.get_instance(self.id)).r.clear()

    property g_exc:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).g_exc
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).g_exc = val
    property record_g_exc:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_g_exc
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_g_exc = val
    def clear_g_exc(self):
        (PopRecorder1.get_instance(self.id)).g_exc.clear()

    property g_inh:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).g_inh
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).g_inh = val
    property record_g_inh:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_g_inh
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_g_inh = val
    def clear_g_inh(self):
        (PopRecorder1.get_instance(self.id)).g_inh.clear()

    property spike:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).spike
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).spike = val
    property record_spike:
        def __get__(self): return (PopRecorder1.get_instance(self.id)).record_spike
        def __set__(self, val): (PopRecorder1.get_instance(self.id)).record_spike = val
    def clear_spike(self):
        (PopRecorder1.get_instance(self.id)).clear_spike()

# Population Monitor wrapper
@cython.auto_pickle(True)
cdef class PopRecorder2_wrapper:
    cdef int id
    def __init__(self, list ranks, int period, period_offset, long offset):
        self.id = PopRecorder2.create_instance(ranks, period, period_offset, offset)

    def size_in_bytes(self):
        return (PopRecorder2.get_instance(self.id)).size_in_bytes()

    def clear(self):
        return (PopRecorder2.get_instance(self.id)).clear()

    property I_CBF:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).I_CBF
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).I_CBF = val
    property record_I_CBF:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_I_CBF
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_I_CBF = val
    def clear_I_CBF(self):
        (PopRecorder2.get_instance(self.id)).I_CBF.clear()

    property s:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).s
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).s = val
    property record_s:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_s
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_s = val
    def clear_s(self):
        (PopRecorder2.get_instance(self.id)).s.clear()

    property f_in:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).f_in
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).f_in = val
    property record_f_in:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_f_in
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_f_in = val
    def clear_f_in(self):
        (PopRecorder2.get_instance(self.id)).f_in.clear()

    property E:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).E
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).E = val
    property record_E:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_E
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_E = val
    def clear_E(self):
        (PopRecorder2.get_instance(self.id)).E.clear()

    property q:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).q
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).q = val
    property record_q:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_q
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_q = val
    def clear_q(self):
        (PopRecorder2.get_instance(self.id)).q.clear()

    property v:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).v
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).v = val
    property record_v:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_v
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_v = val
    def clear_v(self):
        (PopRecorder2.get_instance(self.id)).v.clear()

    property f_out:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).f_out
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).f_out = val
    property record_f_out:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_f_out
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_f_out = val
    def clear_f_out(self):
        (PopRecorder2.get_instance(self.id)).f_out.clear()

    property k_1:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).k_1
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).k_1 = val
    property record_k_1:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_k_1
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_k_1 = val
    def clear_k_1(self):
        (PopRecorder2.get_instance(self.id)).k_1.clear()

    property k_2:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).k_2
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).k_2 = val
    property record_k_2:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_k_2
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_k_2 = val
    def clear_k_2(self):
        (PopRecorder2.get_instance(self.id)).k_2.clear()

    property k_3:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).k_3
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).k_3 = val
    property record_k_3:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_k_3
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_k_3 = val
    def clear_k_3(self):
        (PopRecorder2.get_instance(self.id)).k_3.clear()

    property BOLD:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).BOLD
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).BOLD = val
    property record_BOLD:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_BOLD
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_BOLD = val
    def clear_BOLD(self):
        (PopRecorder2.get_instance(self.id)).BOLD.clear()

    property r:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).r
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).r = val
    property record_r:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_r
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_r = val
    def clear_r(self):
        (PopRecorder2.get_instance(self.id)).r.clear()

    property BOLD_Davis:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).BOLD_Davis
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).BOLD_Davis = val
    property record_BOLD_Davis:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record_BOLD_Davis
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record_BOLD_Davis = val
    def clear_BOLD_Davis(self):
        (PopRecorder2.get_instance(self.id)).BOLD_Davis.clear()

    # Targets
    property _sum_I_CBF:
        def __get__(self): return (PopRecorder2.get_instance(self.id))._sum_I_CBF
        def __set__(self, val): (PopRecorder2.get_instance(self.id))._sum_I_CBF = val
    property record__sum_I_CBF:
        def __get__(self): return (PopRecorder2.get_instance(self.id)).record__sum_I_CBF
        def __set__(self, val): (PopRecorder2.get_instance(self.id)).record__sum_I_CBF = val
    def clear__sum_I_CBF(self):
        (PopRecorder2.get_instance(self.id))._sum_I_CBF.clear()

# Projection Monitor wrapper
@cython.auto_pickle(True)
cdef class ProjRecorder0_wrapper:
    cdef int id
    def __init__(self, list ranks, int period, int period_offset, long offset):
        self.id = ProjRecorder0.create_instance(ranks, period, period_offset, offset)

# Projection Monitor wrapper
@cython.auto_pickle(True)
cdef class ProjRecorder1_wrapper:
    cdef int id
    def __init__(self, list ranks, int period, int period_offset, long offset):
        self.id = ProjRecorder1.create_instance(ranks, period, period_offset, offset)


# User-defined functions


# User-defined constants


# Initialize the network
def pyx_create(double dt):
    initialize(dt)

def pyx_init_rng_dist():
    init_rng_dist()

# Simple progressbar on the command line
def progress(count, total, status=''):
    """
    Prints a progress bar on the command line.

    adapted from: https://gist.github.com/vladignatyev/06860ec2040cb497f0f3

    Modification: The original code set the '\r' at the end, so the bar disappears when finished.
    I moved it to the front, so the last status remains.
    """
    bar_len = 60
    filled_len = int(round(bar_len * count / float(total)))

    percents = round(100.0 * count / float(total), 1)
    bar = '=' * filled_len + '-' * (bar_len - filled_len)

    sys.stdout.write('\r[%s] %s%s ...%s' % (bar, percents, '%', status))
    sys.stdout.flush()

# Simulation for the given number of steps
def pyx_run(int nb_steps, progress_bar):
    cdef int nb, rest
    cdef int batch = 1000
    if nb_steps < batch:
        with nogil:
            run(nb_steps)
    else:
        nb = int(nb_steps/batch)
        rest = nb_steps % batch
        for i in range(nb):
            with nogil:
                run(batch)
            PyErr_CheckSignals()
            if nb > 1 and progress_bar:
                progress(i+1, nb, 'simulate()')
        if rest > 0:
            run(rest)

        if (progress_bar):
            print('\n')

# Simulation for the given number of steps except if a criterion is reached
def pyx_run_until(int nb_steps, list populations, bool mode):
    cdef int nb
    nb = run_until(nb_steps, populations, mode)
    return nb

# Simulate for one step
def pyx_step():
    step()

# Access time
def set_time(t):
    setTime(t)
def get_time():
    return getTime()

# Access dt
def set_dt(double dt):
    setDt(dt)
def get_dt():
    return getDt()


# Set number of threads
def set_number_threads(int n, core_list):
    setNumberThreads(n, core_list)


# Set seed
def set_seed(long seed, int num_sources, use_seed_seq):
    setSeed(seed, num_sources, use_seed_seq)
