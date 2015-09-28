#include <v8.h>
#include <sys/types.h>
#include <node.h>
#include <stdio.h>
#include <node_object_wrap.h>
#include <nan.h>

extern "C" {
	int hll_init(struct HLL *hll, uint8_t bits);
	int hll_load(struct HLL *hll, const void *registers, size_t size);
	void hll_destroy(struct HLL *hll);
	int hll_merge(struct HLL *dst, const struct HLL *src);
	void hll_add(struct HLL *hll, const void *buf, size_t size);
	double hll_count(const struct HLL *hll);
}

#include "../deps/hll/src/hll.h"

namespace hllNative {

using namespace v8;

class HLLBinding : public Nan::ObjectWrap {
	public:
		HLLBinding(unsigned char bits) {
			hll_init(&this->hll, bits);
		}

		~HLLBinding() {
			hll_destroy(&this->hll);
		}

		void add(const char *ptr, size_t size) {
			hll_add(&this->hll, ptr, size);
		}

		size_t count() {
			return (size_t)(hll_count(&this->hll) + 0.4999);
		}

		static NAN_METHOD(New) {
			if (info.IsConstructCall()) {
				double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();

				if(value < 4 || value > 20) {
					Nan::ThrowError("Bits value must be: 4 <= bits <= 20");

					return;
				}

				unsigned char bits = (unsigned char)value;

				HLLBinding* obj = new HLLBinding(bits);
				obj->Wrap(info.This());
				info.GetReturnValue().Set(info.This());
			}
		}

		static NAN_METHOD(Add) {
			if (info.Length() != 1) {
				Nan::ThrowError("Wrong number of arguments");

				return;
			}

			Nan::Utf8String str(info[0]);

			HLLBinding* obj = Nan::ObjectWrap::Unwrap<HLLBinding>(info.Holder());
			obj->add(*str, str.length());
		}

		static NAN_METHOD(Count) {
			HLLBinding* obj = Nan::ObjectWrap::Unwrap<HLLBinding>(info.Holder());

			info.GetReturnValue().Set(Nan::New<Number>(obj->count()));
		}

		static NAN_METHOD(EmptyMethod) {
		}

		static void Init(Handle<Object> exports) {
			Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);

			tpl->SetClassName(Nan::New("HLL").ToLocalChecked());
			tpl->InstanceTemplate()->SetInternalFieldCount(1);

			Nan::SetPrototypeTemplate(tpl, "add", Nan::New<FunctionTemplate>(Add));
			Nan::SetPrototypeTemplate(tpl, "count", Nan::New<FunctionTemplate>(Count));

			exports->Set(Nan::New("HLL").ToLocalChecked(), tpl->GetFunction());
		}


	private:

		HLL hll;

		static Nan::Persistent<Function> constructor;
};

Nan::Persistent<Function> HLLBinding::constructor;
}

NODE_MODULE(hll_native, hllNative::HLLBinding::Init);

