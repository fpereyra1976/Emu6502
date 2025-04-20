#ifndef __MEMORY_HPP_
#define __MEMORY_HPP_

#include<iostream>

#include"common.hpp"

namespace CPU6502{ 
    const Word MEMORY_SIZE = 65535;

    class Memory {
        private:
            Byte data[65536];
        public:
            Memory(){
                for(Word i=0;i<MEMORY_SIZE;i++){
                    data[i] = Byte(0x00);
                }
                // Reset Vector
                this->data[0xFFFC] = 0x00;
                this->data[0xFFFD] = 0x80;
            }

            Byte &Get(Word p){
                // No validation needed. (?)
                return this->data[p];
            }
            void Set(Word p,Byte &v){
                // No validation needed. (?)
                this->data[p] = v;
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