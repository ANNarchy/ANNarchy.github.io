#pragma once
extern long int t;

int addRecorder(class Monitor* recorder);
Monitor* getRecorder(int id);
void removeRecorder(class Monitor* recorder);

/*
 * Recorders
 *
 */
class Monitor
{
public:
    Monitor(std::vector<int> ranks, int period, int period_offset, long int offset) {
        this->ranks = ranks;
        this->period_ = period;
        this->period_offset_ = period_offset;
        this->offset_ = offset;
        if(this->ranks.size() ==1 && this->ranks[0]==-1) // All neurons should be recorded
            this->partial = false;
        else
            this->partial = true;
    };

    ~Monitor() = default;

    virtual void record() = 0;
    virtual void record_targets() = 0;
    virtual long int size_in_bytes() = 0;
    virtual void clear() = 0;

    // Attributes
    bool partial;
    std::vector<int> ranks;
    int period_;
    int period_offset_;
    long int offset_;
};

class PopRecorder0 : public Monitor
{
protected:
    PopRecorder0(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder0 (" << this << ") instantiated." << std::endl;
    #endif

        this->g_exc = std::vector< std::vector< double > >();
        this->record_g_exc = false; 
        this->g_inh = std::vector< std::vector< double > >();
        this->record_g_inh = false; 
        this->I = std::vector< std::vector< double > >();
        this->record_I = false; 
        this->v = std::vector< std::vector< double > >();
        this->record_v = false; 
        this->u = std::vector< std::vector< double > >();
        this->record_u = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->spike = std::map<int,  std::vector< long int > >();
        if(!this->partial){
            for(int i=0; i<pop0.size; i++) {
                this->spike[i]=std::vector<long int>();
            }
        }
        else{
            for(int i=0; i<this->ranks.size(); i++) {
                this->spike[this->ranks[i]]=std::vector<long int>();
            }
        }
        this->record_spike = false; 

    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder0(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder0 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder0* get_instance(int id) {
        return static_cast<PopRecorder0*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder0::record()" << std::endl;
    #endif

        if(this->record_I && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->I.push_back(pop0.I);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.I[this->ranks[i]]);
                }
                this->I.push_back(tmp);
            }
        }
        if(this->record_v && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->v.push_back(pop0.v);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.v[this->ranks[i]]);
                }
                this->v.push_back(tmp);
            }
        }
        if(this->record_u && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->u.push_back(pop0.u);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.u[this->ranks[i]]);
                }
                this->u.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop0.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_spike){
            for(int i=0; i<pop0.spiked.size(); i++){
                if(!this->partial){
                    this->spike[pop0.spiked[i]].push_back(t);
                }
                else{
                    if( std::find(this->ranks.begin(), this->ranks.end(), pop0.spiked[i])!=this->ranks.end() ){
                        this->spike[pop0.spiked[i]].push_back(t);
                    }
                }
            }
        } 
    }

    void record_targets() {

        if(this->record_g_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->g_exc.push_back(pop0.g_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.g_exc[this->ranks[i]]);
                }
                this->g_exc.push_back(tmp);
            }
        }
        if(this->record_g_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->g_inh.push_back(pop0.g_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop0.g_inh[this->ranks[i]]);
                }
                this->g_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable I
        size_in_bytes += sizeof(std::vector<double>) * I.capacity();
        for(auto it=I.begin(); it!= I.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable v
        size_in_bytes += sizeof(std::vector<double>) * v.capacity();
        for(auto it=v.begin(); it!= v.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable u
        size_in_bytes += sizeof(std::vector<double>) * u.capacity();
        for(auto it=u.begin(); it!= u.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // record spike events
        size_in_bytes += sizeof(spike);
        for ( auto it = spike.begin(); it != spike.end(); it++ ) {
            size_in_bytes += sizeof(int); // key
            size_in_bytes += sizeof(long int) * (it->second).capacity(); // value
        }
                
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder0 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->I.begin(); it != this->I.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->I.clear();
    
        for(auto it = this->v.begin(); it != this->v.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->v.clear();
    
        for(auto it = this->u.begin(); it != this->u.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->u.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable g_exc
    std::vector< std::vector< double > > g_exc ;
    bool record_g_exc ; 
    // Local variable g_inh
    std::vector< std::vector< double > > g_inh ;
    bool record_g_inh ; 
    // Local variable I
    std::vector< std::vector< double > > I ;
    bool record_I ; 
    // Local variable v
    std::vector< std::vector< double > > v ;
    bool record_v ; 
    // Local variable u
    std::vector< std::vector< double > > u ;
    bool record_u ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable spike
    std::map<int, std::vector< long int > > spike ;
    bool record_spike ;
    void clear_spike() {
        for ( auto it = spike.begin(); it != spike.end(); it++ ) {
            it->second.clear();
            it->second.shrink_to_fit();
        }
    }

};

class PopRecorder1 : public Monitor
{
protected:
    PopRecorder1(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder1 (" << this << ") instantiated." << std::endl;
    #endif

        this->g_exc = std::vector< std::vector< double > >();
        this->record_g_exc = false; 
        this->g_inh = std::vector< std::vector< double > >();
        this->record_g_inh = false; 
        this->I = std::vector< std::vector< double > >();
        this->record_I = false; 
        this->v = std::vector< std::vector< double > >();
        this->record_v = false; 
        this->u = std::vector< std::vector< double > >();
        this->record_u = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->spike = std::map<int,  std::vector< long int > >();
        if(!this->partial){
            for(int i=0; i<pop1.size; i++) {
                this->spike[i]=std::vector<long int>();
            }
        }
        else{
            for(int i=0; i<this->ranks.size(); i++) {
                this->spike[this->ranks[i]]=std::vector<long int>();
            }
        }
        this->record_spike = false; 

    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder1(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder1 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder1* get_instance(int id) {
        return static_cast<PopRecorder1*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder1::record()" << std::endl;
    #endif

        if(this->record_I && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->I.push_back(pop1.I);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.I[this->ranks[i]]);
                }
                this->I.push_back(tmp);
            }
        }
        if(this->record_v && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->v.push_back(pop1.v);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.v[this->ranks[i]]);
                }
                this->v.push_back(tmp);
            }
        }
        if(this->record_u && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->u.push_back(pop1.u);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.u[this->ranks[i]]);
                }
                this->u.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop1.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_spike){
            for(int i=0; i<pop1.spiked.size(); i++){
                if(!this->partial){
                    this->spike[pop1.spiked[i]].push_back(t);
                }
                else{
                    if( std::find(this->ranks.begin(), this->ranks.end(), pop1.spiked[i])!=this->ranks.end() ){
                        this->spike[pop1.spiked[i]].push_back(t);
                    }
                }
            }
        } 
    }

    void record_targets() {

        if(this->record_g_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->g_exc.push_back(pop1.g_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.g_exc[this->ranks[i]]);
                }
                this->g_exc.push_back(tmp);
            }
        }
        if(this->record_g_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->g_inh.push_back(pop1.g_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.g_inh[this->ranks[i]]);
                }
                this->g_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable I
        size_in_bytes += sizeof(std::vector<double>) * I.capacity();
        for(auto it=I.begin(); it!= I.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable v
        size_in_bytes += sizeof(std::vector<double>) * v.capacity();
        for(auto it=v.begin(); it!= v.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable u
        size_in_bytes += sizeof(std::vector<double>) * u.capacity();
        for(auto it=u.begin(); it!= u.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // record spike events
        size_in_bytes += sizeof(spike);
        for ( auto it = spike.begin(); it != spike.end(); it++ ) {
            size_in_bytes += sizeof(int); // key
            size_in_bytes += sizeof(long int) * (it->second).capacity(); // value
        }
                
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder1 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->I.begin(); it != this->I.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->I.clear();
    
        for(auto it = this->v.begin(); it != this->v.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->v.clear();
    
        for(auto it = this->u.begin(); it != this->u.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->u.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable g_exc
    std::vector< std::vector< double > > g_exc ;
    bool record_g_exc ; 
    // Local variable g_inh
    std::vector< std::vector< double > > g_inh ;
    bool record_g_inh ; 
    // Local variable I
    std::vector< std::vector< double > > I ;
    bool record_I ; 
    // Local variable v
    std::vector< std::vector< double > > v ;
    bool record_v ; 
    // Local variable u
    std::vector< std::vector< double > > u ;
    bool record_u ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable spike
    std::map<int, std::vector< long int > > spike ;
    bool record_spike ;
    void clear_spike() {
        for ( auto it = spike.begin(); it != spike.end(); it++ ) {
            it->second.clear();
            it->second.shrink_to_fit();
        }
    }

};

class PopRecorder2 : public Monitor
{
protected:
    PopRecorder2(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder2 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_I_CBF = std::vector< std::vector< double > >();
        this->record__sum_I_CBF = false; 
        this->I_CBF = std::vector< std::vector< double > >();
        this->record_I_CBF = false; 
        this->s = std::vector< std::vector< double > >();
        this->record_s = false; 
        this->f_in = std::vector< std::vector< double > >();
        this->record_f_in = false; 
        this->E = std::vector< std::vector< double > >();
        this->record_E = false; 
        this->q = std::vector< std::vector< double > >();
        this->record_q = false; 
        this->v = std::vector< std::vector< double > >();
        this->record_v = false; 
        this->f_out = std::vector< std::vector< double > >();
        this->record_f_out = false; 
        this->k_1 = std::vector< std::vector< double > >();
        this->record_k_1 = false; 
        this->k_2 = std::vector< std::vector< double > >();
        this->record_k_2 = false; 
        this->k_3 = std::vector< std::vector< double > >();
        this->record_k_3 = false; 
        this->BOLD = std::vector< std::vector< double > >();
        this->record_BOLD = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->BOLD_Davis = std::vector< std::vector< double > >();
        this->record_BOLD_Davis = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder2(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder2 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder2* get_instance(int id) {
        return static_cast<PopRecorder2*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder2::record()" << std::endl;
    #endif

        if(this->record_I_CBF && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->I_CBF.push_back(pop2.I_CBF);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.I_CBF[this->ranks[i]]);
                }
                this->I_CBF.push_back(tmp);
            }
        }
        if(this->record_s && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->s.push_back(pop2.s);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.s[this->ranks[i]]);
                }
                this->s.push_back(tmp);
            }
        }
        if(this->record_f_in && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->f_in.push_back(pop2.f_in);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.f_in[this->ranks[i]]);
                }
                this->f_in.push_back(tmp);
            }
        }
        if(this->record_E && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->E.push_back(pop2.E);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.E[this->ranks[i]]);
                }
                this->E.push_back(tmp);
            }
        }
        if(this->record_q && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->q.push_back(pop2.q);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.q[this->ranks[i]]);
                }
                this->q.push_back(tmp);
            }
        }
        if(this->record_v && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->v.push_back(pop2.v);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.v[this->ranks[i]]);
                }
                this->v.push_back(tmp);
            }
        }
        if(this->record_f_out && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->f_out.push_back(pop2.f_out);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.f_out[this->ranks[i]]);
                }
                this->f_out.push_back(tmp);
            }
        }
        if(this->record_k_1 && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->k_1.push_back(pop2.k_1);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.k_1[this->ranks[i]]);
                }
                this->k_1.push_back(tmp);
            }
        }
        if(this->record_k_2 && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->k_2.push_back(pop2.k_2);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.k_2[this->ranks[i]]);
                }
                this->k_2.push_back(tmp);
            }
        }
        if(this->record_k_3 && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->k_3.push_back(pop2.k_3);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.k_3[this->ranks[i]]);
                }
                this->k_3.push_back(tmp);
            }
        }
        if(this->record_BOLD && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->BOLD.push_back(pop2.BOLD);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.BOLD[this->ranks[i]]);
                }
                this->BOLD.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop2.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_BOLD_Davis && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->BOLD_Davis.push_back(pop2.BOLD_Davis);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.BOLD_Davis[this->ranks[i]]);
                }
                this->BOLD_Davis.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_I_CBF && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_I_CBF.push_back(pop2._sum_I_CBF);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2._sum_I_CBF[this->ranks[i]]);
                }
                this->_sum_I_CBF.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable I_CBF
        size_in_bytes += sizeof(std::vector<double>) * I_CBF.capacity();
        for(auto it=I_CBF.begin(); it!= I_CBF.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable s
        size_in_bytes += sizeof(std::vector<double>) * s.capacity();
        for(auto it=s.begin(); it!= s.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable f_in
        size_in_bytes += sizeof(std::vector<double>) * f_in.capacity();
        for(auto it=f_in.begin(); it!= f_in.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable E
        size_in_bytes += sizeof(std::vector<double>) * E.capacity();
        for(auto it=E.begin(); it!= E.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable q
        size_in_bytes += sizeof(std::vector<double>) * q.capacity();
        for(auto it=q.begin(); it!= q.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable v
        size_in_bytes += sizeof(std::vector<double>) * v.capacity();
        for(auto it=v.begin(); it!= v.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable f_out
        size_in_bytes += sizeof(std::vector<double>) * f_out.capacity();
        for(auto it=f_out.begin(); it!= f_out.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable k_1
        size_in_bytes += sizeof(std::vector<double>) * k_1.capacity();
        for(auto it=k_1.begin(); it!= k_1.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable k_2
        size_in_bytes += sizeof(std::vector<double>) * k_2.capacity();
        for(auto it=k_2.begin(); it!= k_2.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable k_3
        size_in_bytes += sizeof(std::vector<double>) * k_3.capacity();
        for(auto it=k_3.begin(); it!= k_3.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable BOLD
        size_in_bytes += sizeof(std::vector<double>) * BOLD.capacity();
        for(auto it=BOLD.begin(); it!= BOLD.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable BOLD_Davis
        size_in_bytes += sizeof(std::vector<double>) * BOLD_Davis.capacity();
        for(auto it=BOLD_Davis.begin(); it!= BOLD_Davis.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder2 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->I_CBF.begin(); it != this->I_CBF.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->I_CBF.clear();
    
        for(auto it = this->s.begin(); it != this->s.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->s.clear();
    
        for(auto it = this->f_in.begin(); it != this->f_in.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->f_in.clear();
    
        for(auto it = this->E.begin(); it != this->E.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->E.clear();
    
        for(auto it = this->q.begin(); it != this->q.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->q.clear();
    
        for(auto it = this->v.begin(); it != this->v.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->v.clear();
    
        for(auto it = this->f_out.begin(); it != this->f_out.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->f_out.clear();
    
        for(auto it = this->k_1.begin(); it != this->k_1.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->k_1.clear();
    
        for(auto it = this->k_2.begin(); it != this->k_2.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->k_2.clear();
    
        for(auto it = this->k_3.begin(); it != this->k_3.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->k_3.clear();
    
        for(auto it = this->BOLD.begin(); it != this->BOLD.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->BOLD.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    
        for(auto it = this->BOLD_Davis.begin(); it != this->BOLD_Davis.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->BOLD_Davis.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_I_CBF
    std::vector< std::vector< double > > _sum_I_CBF ;
    bool record__sum_I_CBF ; 
    // Local variable I_CBF
    std::vector< std::vector< double > > I_CBF ;
    bool record_I_CBF ; 
    // Local variable s
    std::vector< std::vector< double > > s ;
    bool record_s ; 
    // Local variable f_in
    std::vector< std::vector< double > > f_in ;
    bool record_f_in ; 
    // Local variable E
    std::vector< std::vector< double > > E ;
    bool record_E ; 
    // Local variable q
    std::vector< std::vector< double > > q ;
    bool record_q ; 
    // Local variable v
    std::vector< std::vector< double > > v ;
    bool record_v ; 
    // Local variable f_out
    std::vector< std::vector< double > > f_out ;
    bool record_f_out ; 
    // Local variable k_1
    std::vector< std::vector< double > > k_1 ;
    bool record_k_1 ; 
    // Local variable k_2
    std::vector< std::vector< double > > k_2 ;
    bool record_k_2 ; 
    // Local variable k_3
    std::vector< std::vector< double > > k_3 ;
    bool record_k_3 ; 
    // Local variable BOLD
    std::vector< std::vector< double > > BOLD ;
    bool record_BOLD ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable BOLD_Davis
    std::vector< std::vector< double > > BOLD_Davis ;
    bool record_BOLD_Davis ; 
};

class ProjRecorder0 : public Monitor
{
protected:
    ProjRecorder0(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder0 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj0.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder0(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder0 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder0* get_instance(int id) {
        return static_cast<ProjRecorder0*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor0::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder1 : public Monitor
{
protected:
    ProjRecorder1(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder1 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj1.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder1(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder1 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder1* get_instance(int id) {
        return static_cast<ProjRecorder1*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor1::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

