#include "plugin.hpp"
#include "Chicken.h"


struct ChickenModule : Module {
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
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	Chicken_process_type processor;

	ChickenModule() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(KNOB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB4_PARAM, 0.f, 1.f, 0.f, "");

		Chicken_process_init(processor);
	}

	void process(const ProcessArgs &args) override {

		Chicken_setKnob1(processor, params[KNOB1_PARAM].value);
		Chicken_setKnob2(processor, params[KNOB2_PARAM].value);
		Chicken_setKnob3(processor, params[KNOB3_PARAM].value);
		Chicken_setKnob4(processor, params[KNOB4_PARAM].value);
		Chicken_isClockConnected(processor, inputs[CLOCK_INPUT].active);

		lights[BLINK_LIGHT].setBrightness(inputs[CLOCK_INPUT].active ? 1.f: 0.f);

		float clk = inputs[CLOCK_INPUT].value / 10.0f;
		float mod1 = inputs[MOD1_INPUT].value / 10.0f;
		float mod2 = inputs[MOD2_INPUT].value / 10.0f;

		Chicken_process(processor, clk, mod1, mod2);
		outputs[OUT1_OUTPUT].value = Chicken_process_ret_0(processor) * 10.0f;
		outputs[OUT2_OUTPUT].value = Chicken_process_ret_1(processor) * 10.0f;
	}
};


struct ChickenModuleWidget : ModuleWidget {
	ChickenModuleWidget(ChickenModule *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ChickenModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.0, 40.0)), module, ChickenModule::KNOB1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.0, 60.0)), module, ChickenModule::KNOB2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.0, 80.0)), module, ChickenModule::KNOB3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.0, 100.0)), module, ChickenModule::KNOB4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0, 40.0)), module, ChickenModule::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0, 60.0)), module, ChickenModule::MOD1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.0, 80.0)), module, ChickenModule::MOD2_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.0, 100.0)), module, ChickenModule::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.273, 115.778)), module, ChickenModule::OUT2_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 18.472)), module, ChickenModule::BLINK_LIGHT));

	}
};

Model *modelChickenModule = createModel<ChickenModule, ChickenModuleWidget>("ChickenModule");
