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
	${OBJECTDIR}/src/EXTMR/Exceptions/VariantTypeException.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/NonAssignableException.o \
	${OBJECTDIR}/src/EXTMR/Variant.o \
	${OBJECTDIR}/src/EXTMR/Type.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/PropertySetException.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/NonCopyableException.o \
	${OBJECTDIR}/src/EXTMR/Member.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/NonInstantiableException.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/NotFoundExceptions.o \
	${OBJECTDIR}/src/EXTMR/TypeRegister.o \
	${OBJECTDIR}/src/EXTMR/Method.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/VariantCostnessException.o \
	${OBJECTDIR}/src/EXTMR/Template.o \
	${OBJECTDIR}/src/EXTMR/PrimitiveType.o \
	${OBJECTDIR}/src/EXTMR/CompoundClass.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/PropertyRangeException.o \
	${OBJECTDIR}/src/EXTMR/ArrayType.o \
	${OBJECTDIR}/src/EXTMR/Property.o \
	${OBJECTDIR}/src/EXTMR/Class.o \
	${OBJECTDIR}/src/EXTMR/Exceptions/NonDestructibleException.o \
	${OBJECTDIR}/src/EXTMR/PointerType.o


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

${OBJECTDIR}/src/EXTMR/Exceptions/VariantTypeException.o: src/EXTMR/Exceptions/VariantTypeException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/VariantTypeException.o src/EXTMR/Exceptions/VariantTypeException.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/NonAssignableException.o: src/EXTMR/Exceptions/NonAssignableException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/NonAssignableException.o src/EXTMR/Exceptions/NonAssignableException.cpp

${OBJECTDIR}/src/EXTMR/Variant.o: src/EXTMR/Variant.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Variant.o src/EXTMR/Variant.cpp

${OBJECTDIR}/src/EXTMR/Type.o: src/EXTMR/Type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Type.o src/EXTMR/Type.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/PropertySetException.o: src/EXTMR/Exceptions/PropertySetException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/PropertySetException.o src/EXTMR/Exceptions/PropertySetException.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/NonCopyableException.o: src/EXTMR/Exceptions/NonCopyableException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/NonCopyableException.o src/EXTMR/Exceptions/NonCopyableException.cpp

${OBJECTDIR}/src/EXTMR/Member.o: src/EXTMR/Member.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Member.o src/EXTMR/Member.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/NonInstantiableException.o: src/EXTMR/Exceptions/NonInstantiableException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/NonInstantiableException.o src/EXTMR/Exceptions/NonInstantiableException.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/NotFoundExceptions.o: src/EXTMR/Exceptions/NotFoundExceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/NotFoundExceptions.o src/EXTMR/Exceptions/NotFoundExceptions.cpp

${OBJECTDIR}/src/EXTMR/TypeRegister.o: src/EXTMR/TypeRegister.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/TypeRegister.o src/EXTMR/TypeRegister.cpp

${OBJECTDIR}/src/EXTMR/Method.o: src/EXTMR/Method.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Method.o src/EXTMR/Method.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/VariantCostnessException.o: src/EXTMR/Exceptions/VariantCostnessException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/VariantCostnessException.o src/EXTMR/Exceptions/VariantCostnessException.cpp

${OBJECTDIR}/src/EXTMR/Template.o: src/EXTMR/Template.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Template.o src/EXTMR/Template.cpp

${OBJECTDIR}/src/EXTMR/PrimitiveType.o: src/EXTMR/PrimitiveType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/PrimitiveType.o src/EXTMR/PrimitiveType.cpp

${OBJECTDIR}/src/EXTMR/CompoundClass.o: src/EXTMR/CompoundClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/CompoundClass.o src/EXTMR/CompoundClass.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/PropertyRangeException.o: src/EXTMR/Exceptions/PropertyRangeException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/PropertyRangeException.o src/EXTMR/Exceptions/PropertyRangeException.cpp

${OBJECTDIR}/src/EXTMR/ArrayType.o: src/EXTMR/ArrayType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/ArrayType.o src/EXTMR/ArrayType.cpp

${OBJECTDIR}/src/EXTMR/Property.o: src/EXTMR/Property.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Property.o src/EXTMR/Property.cpp

${OBJECTDIR}/src/EXTMR/Class.o: src/EXTMR/Class.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Class.o src/EXTMR/Class.cpp

${OBJECTDIR}/src/EXTMR/Exceptions/NonDestructibleException.o: src/EXTMR/Exceptions/NonDestructibleException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR/Exceptions
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/Exceptions/NonDestructibleException.o src/EXTMR/Exceptions/NonDestructibleException.cpp

${OBJECTDIR}/src/EXTMR/PointerType.o: src/EXTMR/PointerType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/EXTMR
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EXTMR/PointerType.o src/EXTMR/PointerType.cpp

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