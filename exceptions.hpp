#ifndef __EXCEPTIONS_HPP
#define __EXCEPTIONS_HPP

namespace CPU6502{   
    class CPUException :  public std::exception{
        public:
        const char* what() const noexcept override {
            return "CPUException";
         }
    };
    class CPUInvalidOpCodeExcepcion : public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUInvalidOpCodeExcepcion";
         }
    };

    class CPUCyleExecutionException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCyleExecutionException";
         }
    };

    class CPUCInvalidInstructionTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCInvalidInstructionTypeException";
         }
    };

    class CPUCOnTickException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCOnTickException";
         }
    };

    class CPUInvalidInstructionTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUInvalidInstructionTypeException";
         }
    };

    class CPUNoOperandsImplicitTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUNoOperandsImplicitTypeException";
         }
    };

    class CPUNoFetchValueOnInmediatTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUNoFetchValueOnInmediatTypeException";
         }
    };

    class CPUInstructionInvalidOperation: public CPUException{
        public:
        const char* what() const noexcept override {
            return "CPUInstructionInvalidOperation";
         }  
    };
}

#endif // __EXCEPTIONS_HPP