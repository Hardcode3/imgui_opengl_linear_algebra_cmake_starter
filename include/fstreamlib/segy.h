#ifndef SEGY_H
#define SEGY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>

struct SegyHeader {
    char text[3200];
    int32_t jobID;
    int32_t lineNumber;
    int32_t reelNumber;
    int16_t numTraces;
    int16_t numAuxTraces;
    uint16_t sampleInterval;
    uint16_t sampleIntervalOriginal;
    uint16_t numSamplesPerTrace;
    uint16_t numSamplesPerTraceOriginal;
    uint16_t dataSampleFormat;
    uint16_t ensembleFold;
    uint16_t traceSorting;
    uint16_t verticalSumCode;
    uint16_t sweepFrequencyStart;
    uint16_t sweepFrequencyEnd;
    uint16_t sweepLength;
    uint16_t sweepType;
    uint16_t traceNumber;
    uint16_t traceNumberStep;
    int16_t traceNumberField;
    int16_t traceNumberFieldStep;
    int16_t traceIdentificationCode;
    uint16_t scalarTraceHeader;
    uint16_t scalarData;
    int16_t dataSampleCount;
    int16_t dataSampleCountOriginal;
    uint16_t dataSampleInterval;
    uint16_t dataSampleIntervalOriginal;
    int16_t gainType;
    int16_t instrumentGainConstant;
    int16_t instrumentInitialGain;
    int16_t correlatedTraces;
    int16_t sweepLengthStart;
    int16_t sweepLengthEnd;
    int16_t sweepLengthChannel;
    int16_t sweepTypeChannel;
    int16_t sweepTraceTaperLengthStart;
    int16_t sweepTraceTaperLengthEnd;
    int16_t taperType;
    int16_t correlatedTracesTaper;
    uint16_t binaryGainRecovered;
    uint16_t amplitudeRecoveryMethod;
    int16_t measurementSystem;
    int16_t impulseSignalPolarity;
    uint16_t vibratoryPolarityCode;
    int16_t unassigned1[14];
    int32_t extendedHeader;
};

struct TraceHeader {
    int32_t traceSequenceLine;
    int32_t traceSequenceFile;
    int32_t fieldRecordNumber;
    int32_t traceNumber;
    int32_t energySourcePoint;
    int32_t ensembleNumber;
    int32_t traceNumberWithinEnsemble;
    int16_t traceIdentificationCode;
    int16_t traceVerticalAxis;
    int32_t dataSampleCount;
    int32_t dataSampleCountOrig;
    int32_t dataSampleInterval;
    int32_t dataSampleIntervalOrig;
    int32_t traceSampleInterval;
    int32_t traceSampleIntervalOrig;
    int16_t dataSampleFormat;
    int16_t ensembleFold;
    int32_t traceMeasurementUnit;
    float traceMeasurementUnitMultiplier;
    int16_t transductionConstantMantissa;
    int16_t transductionConstantPower;
    int16_t transductionUnit;
    int16_t deviceTraceIdentifier;
    int16_t scalarTraceHeader;
    int16_t sourceTypeOrientation;
    int32_t sourceEnergyDirectionMantissa;
    int32_t sourceEnergyDirectionExponent;
    int32_t sourceMeasurementMantissa;
    int32_t sourceMeasurementExponent;
    float sourceMeasurementUnitMultiplier;
    int16_t unassigned1[10];
    int32_t ensembleXCoord;
    int32_t ensembleYCoord;
    int32_t groupXCoord;
    int32_t groupYCoord;
    int16_t coordinateUnits;
    int16_t unassigned2[5];
    int32_t delayRecordingTime;
    int32_t delayRecordingTimeOrig;
    int16_t weightingFactor;
    int16_t unassigned3[7];
    int16_t correlatedTraces;
    int16_t binaryGainRecovered;
    int16_t amplitudeRecoveryMethod;
    int16_t measurementSystem;
    int16_t impulseSignalPolarity;
    int16_t vibratoryPolarityCode;
    int16_t unassigned4[17];
};

class SegyReader {
public:
    SegyReader(const std::string& filename);

    const std::vector<std::vector<float>>& getData() const;

    const std::vector<TraceHeader>& getTraceHeaders() const;

private:
   
    };

#endif