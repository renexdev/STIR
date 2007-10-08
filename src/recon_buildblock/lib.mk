#
# $Id$
#

dir := recon_buildblock
$(dir)_LIB_SOURCES:= ForwardProjectorByBin.cxx \
	ForwardProjectorByBinUsingRayTracing.cxx \
	ForwardProjectorByBinUsingRayTracing_Siddon.cxx \
	BackProjectorByBin.cxx \
	BackProjectorByBinUsingInterpolation.cxx \
	BackProjectorByBinUsingInterpolation_linear.cxx \
	BackProjectorByBinUsingInterpolation_piecewise_linear.cxx \
	Reconstruction.cxx \
	AnalyticReconstruction.cxx \
	IterativeReconstruction.cxx \
	distributable.cxx \
	DataSymmetriesForBins.cxx \
	DataSymmetriesForDensels.cxx \
	TrivialDataSymmetriesForBins.cxx \
	DataSymmetriesForBins_PET_CartesianGrid.cxx \
	SymmetryOperation.cxx \
	SymmetryOperations_PET_CartesianGrid.cxx \
	ProjMatrixElemsForOneBin.cxx \
	ProjMatrixElemsForOneDensel.cxx \
	ProjMatrixByBin.cxx \
	ProjMatrixByBinUsingRayTracing.cxx \
	ForwardProjectorByBinUsingProjMatrixByBin.cxx \
	BackProjectorByBinUsingProjMatrixByBin.cxx \
	RayTraceVoxelsOnCartesianGrid.cxx \
	ProjectorByBinPair.cxx \
	ProjectorByBinPairUsingProjMatrixByBin.cxx \
	ProjectorByBinPairUsingSeparateProjectors.cxx \
	BinNormalisation.cxx \
	ChainedBinNormalisation.cxx \
	BinNormalisationFromProjData.cxx \
	TrivialBinNormalisation.cxx \
	BinNormalisationFromAttenuationImage.cxx \
	GeneralisedPrior.cxx \
	ProjDataRebinning.cxx \
	GeneralisedPrior.cxx \
	QuadraticPrior.cxx \
	FilterRootPrior.cxx \
	GeneralisedObjectiveFunction.cxx \
	PoissonLogLikelihoodWithLinearModelForMean.cxx \
	PoissonLogLikelihoodWithLinearModelForMeanAndProjData.cxx \
	PoissonLogLikelihoodWithLinearModelForMeanAndListModeData.cxx \
	PoissonLogLikelihoodWithLinearModelForMeanAndListModeDataWithProjMatrixByBin.cxx

ifeq ($(HAVE_LLN_MATRIX),1)
$(dir)_LIB_SOURCES += \
	BinNormalisationFromECAT7.cxx
endif


$(dir)_REGISTRY_SOURCES:= $(dir)_registries.cxx

include $(WORKSPACE)/lib.mk












