
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "Chicken.h"

float Chicken_slew(Chicken__ctx_type_1 &_ctx, float x, float rate){
   float diff;
   diff = (x + (- _ctx.state));
   float y;
   if(diff > rate){
      y = rate;
   }
   else
   {
      if(diff < (- rate)){
         y = (- rate);
      }
      else
      {
         y = diff;
      }
   }
   _ctx.state = (_ctx.state + y);
   return _ctx.state;
}

void Chicken__ctx_type_2_init(Chicken__ctx_type_2 &_output_){
   Chicken__ctx_type_2 _ctx;
   _ctx.sample2 = 0.0f;
   _ctx.sample1 = 0.0f;
   _ctx.process_ret_1 = 0.0f;
   _ctx.process_ret_0 = 0.0f;
   _ctx.knob4 = 0.0f;
   _ctx.knob3 = 0.0f;
   _ctx.knob2 = 0.0f;
   _ctx.knob1 = 0.0f;
   Chicken__ctx_type_1_init(_ctx._inst6);
   Chicken__ctx_type_1_init(_ctx._inst5);
   Chicken__ctx_type_0_init(_ctx._inst3);
   _output_ = _ctx;
   return ;
}

void Chicken_process(Chicken__ctx_type_2 &_ctx, float clock, float mod1, float mod2){
   if(Chicken_edge(_ctx._inst3,(clock > 0.2f))){
      _ctx.sample1 = (-1.f + (2.f * float_random()));
      _ctx.sample2 = (-1.f + (2.f * float_random()));
   }
   float offset;
   offset = (2.f * (-0.5f + _ctx.knob3));
   float out1;
   out1 = (offset + (_ctx.knob2 * Chicken_slew(_ctx._inst5,_ctx.sample1,(0.001f * _ctx.knob1))));
   float out2;
   out2 = (offset + (_ctx.knob2 * Chicken_slew(_ctx._inst6,_ctx.sample2,(0.001f * _ctx.knob1))));
   _ctx.process_ret_0 = out1;
   _ctx.process_ret_1 = out2;
   return ;
}


