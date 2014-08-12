#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/XM/ArrayType.o \
	${OBJECTDIR}/src/XM/Class.o \
	${OBJECTDIR}/src/XM/CompoundClass.o \
	${OBJECTDIR}/src/XM/Exceptions/MembersExceptions.o \
	${OBJECTDIR}/src/XM/Exceptions/NotFoundExceptions.o \
	${OBJECTDIR}/src/XM/Exceptions/PropertyRangeException.o \
	${OBJECTDIR}/src/XM/Exceptions/PropertySetException.o \
	${OBJECTDIR}/src/XM/Exceptions/VariantCostnessException.o \
	${OBJECTDIR}/src/XM/Exceptions/VariantTypeException.o \
	${OBJECTDIR}/src/XM/Function.o \
	${OBJECTDIR}/src/XM/Member.o \
	${OBJECTDIR}/src/XM/Method.o \
	${OBJECTDIR}/src/XM/Name.o \
	${OBJECTDIR}/src/XM/Namespace.o \
	${OBJECTDIR}/src/XM/OtherMembers.o \
	${OBJECTDIR}/src/XM/PointerType.o \
	${OBJECTDIR}/src/XM/PrimitiveType.o \
	${OBJECTDIR}/src/XM/Property.o \
	${OBJECTDIR}/src/XM/RefCaster.o \
	${OBJECTDIR}/src/XM/RefVariant.o \
	${OBJECTDIR}/src/XM/Template.o \
	${OBJECTDIR}/src/XM/Type.o \
	${OBJECTDIR}/src/XM/TypeRegister.o \
	${OBJECTDIR}/src/XM/Variant.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a

${OBJECTDIR}/src/XM/ArrayType.o: src/XM/ArrayType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/ArrayType.o src/XM/ArrayType.cpp

${OBJECTDIR}/src/XM/Class.o: src/XM/Class.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Class.o src/XM/Class.cpp

${OBJECTDIR}/src/XM/CompoundClass.o: src/XM/CompoundClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/CompoundClass.o src/XM/CompoundClass.cpp

${OBJECTDIR}/src/XM/Exceptions/MembersExceptions.o: src/XM/Exceptions/MembersExceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/MembersExceptions.o src/XM/Exceptions/MembersExceptions.cpp

${OBJECTDIR}/src/XM/Exceptions/NotFoundExceptions.o: src/XM/Exceptions/NotFoundExceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/NotFoundExceptions.o src/XM/Exceptions/NotFoundExceptions.cpp

${OBJECTDIR}/src/XM/Exceptions/PropertyRangeException.o: src/XM/Exceptions/PropertyRangeException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/PropertyRangeException.o src/XM/Exceptions/PropertyRangeException.cpp

${OBJECTDIR}/src/XM/Exceptions/PropertySetException.o: src/XM/Exceptions/PropertySetException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/PropertySetException.o src/XM/Exceptions/PropertySetException.cpp

${OBJECTDIR}/src/XM/Exceptions/VariantCostnessException.o: src/XM/Exceptions/VariantCostnessException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/VariantCostnessException.o src/XM/Exceptions/VariantCostnessException.cpp

${OBJECTDIR}/src/XM/Exceptions/VariantTypeException.o: src/XM/Exceptions/VariantTypeException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM/Exceptions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Exceptions/VariantTypeException.o src/XM/Exceptions/VariantTypeException.cpp

${OBJECTDIR}/src/XM/Function.o: src/XM/Function.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Function.o src/XM/Function.cpp

${OBJECTDIR}/src/XM/Member.o: src/XM/Member.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Member.o src/XM/Member.cpp

${OBJECTDIR}/src/XM/Method.o: src/XM/Method.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Method.o src/XM/Method.cpp

${OBJECTDIR}/src/XM/Name.o: src/XM/Name.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Name.o src/XM/Name.cpp

${OBJECTDIR}/src/XM/Namespace.o: src/XM/Namespace.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Namespace.o src/XM/Namespace.cpp

${OBJECTDIR}/src/XM/OtherMembers.o: src/XM/OtherMembers.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/OtherMembers.o src/XM/OtherMembers.cpp

${OBJECTDIR}/src/XM/PointerType.o: src/XM/PointerType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/PointerType.o src/XM/PointerType.cpp

${OBJECTDIR}/src/XM/PrimitiveType.o: src/XM/PrimitiveType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/PrimitiveType.o src/XM/PrimitiveType.cpp

${OBJECTDIR}/src/XM/Property.o: src/XM/Property.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Property.o src/XM/Property.cpp

${OBJECTDIR}/src/XM/RefCaster.o: src/XM/RefCaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/RefCaster.o src/XM/RefCaster.cpp

${OBJECTDIR}/src/XM/RefVariant.o: src/XM/RefVariant.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/RefVariant.o src/XM/RefVariant.cpp

${OBJECTDIR}/src/XM/Template.o: src/XM/Template.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Template.o src/XM/Template.cpp

${OBJECTDIR}/src/XM/Type.o: src/XM/Type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Type.o src/XM/Type.cpp

${OBJECTDIR}/src/XM/TypeRegister.o: src/XM/TypeRegister.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/TypeRegister.o src/XM/TypeRegister.cpp

${OBJECTDIR}/src/XM/Variant.o: src/XM/Variant.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/XM
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XM/Variant.o src/XM/Variant.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libextendedmirror.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
