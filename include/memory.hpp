#ifndef __MEMORY_HPP_
#define __MEMORY_HPP_

#include<iostream>
#include<iomanip>

#include"common.hpp"

namespace CPU6502{ 
    const Word MEMORY_SIZE = 0xffff;

    class Memory {
        private:
            std::array<Byte, MEMORY_SIZE+1> data;
        public:
            Memory(){  
                this->Initialise();
            }

            Byte &Get(Word p){
                return this->data[p];
            }

            const Byte& Get(Word p) const {
                return this->data[p];
            }
            
            void Set(Word p,Byte &v){
                // No validation needed. (?)
                this->data[p] = v;
            }

            void dump(){
                std::cout<< "Inicializando Dump" << std::endl;
                for (unsigned int i=0;i <= MEMORY_SIZE;i++){
                    std::cout << std::hex << std::setw(2) << std::setfill('0') << this->data[i] << "\t";
                }
                std::cout << std::endl;
                std::cout<< "Fin Dump" << std::endl;
            }

            void Initialise(){
                std::cout<< "Inicializando Vector" << std::endl;
                data.fill(0);  // Inicializa todo el array con 0.

                // Reset Vector
                data[0xFFFC] = 0x00;
                data[0xFFFD] = 0x80;
                std::cout<< "Fin Inicializando Vector" << std::endl;
            }

            // Lectura y escritura
            Byte& operator[](Word p) {
                return Get(p);
            }

            // Solo lectura (si el objeto es const)
            const Byte& operator[](Word p) const {
                return Get(p);
            }
    };
};

#endif