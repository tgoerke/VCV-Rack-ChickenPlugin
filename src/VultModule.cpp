#include "plugin.hpp"
#include "Chicken.h"


struct VultModule : Module {
	enum ParamIds {
		KNOB1_PARAM,
		KNOB2_PARAM,
		KNOB3_PARAM,
		KNOB4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		MOD1_INPUT,
		MOD2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	Chicken_process_type processor;

	VultModule() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(KNOB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB4_PARAM, 0.f, 1.f, 0.f, "");

		Chicken_process_init(processor);
	}

	void process(const ProcessArgs &args) override {
		float clk = inputs[CLOCK_INPUT].value / 10.0f;
		float mod1 = inputs[MOD1_INPUT].value / 10.0f;
		float mod2 = inputs[MOD2_INPUT].value / 10.0f;

		float out = Chicken_process(processor, clk, mod1, mod2);
		outputs[OUT_OUTPUT].value = out * 10.0f;
		//outputs[OUTPUT].setVoltage(5.f * sine);
	}
};


struct VultModuleWidget : ModuleWidget {
	VultModuleWidget(VultModule *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VultModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 32.517)), module, VultModule::KNOB1_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.11, 45.197)), module, VultModule::KNOB2_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.11, 57.051)), module, VultModule::KNOB3_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.11, 68.904)), module, VultModule::KNOB4_PARAM));

    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 81.993)), module, VultModule::CLOCK_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.395, 93.542)), module, VultModule::MOD1_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.395, 105.395)), module, VultModule::MOD2_INPUT));

    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 118.308)), module, VultModule::OUT_OUTPUT));

    addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 18.472)), module, VultModule::BLINK_LIGHT));

	}
};

Model *modelVultModule = createModel<VultModule, VultModuleWidget>("VultModule");
