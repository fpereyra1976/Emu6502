#ifndef __MEMORY_HPP_
#define __MEMORY_HPP_

#include"common.hpp"

namespace CPU6502{
    
    class Memory {
        private:
            Byte data[65536];
        public:
            Byte& Get(Word p){
                // No validation needed. (?)
                return data[p];
            }
            void Set(Word p,Byte v){
                // No validation needed. (?)
                data[p] = v;
            }

            void Initialise(){
                for (unsigned int i=0; i<sizeof(data);i++){
                    this->data[i]=0;
                }
            }

            Byte& operator[](Word p){
                return this->Get(p);
            }
    };
};

#endif