#include <ruby/ruby.h>
#include <ruby/debug.h>

static void on_newobj_event(RB_UNUSED_VAR(VALUE _), RB_UNUSED_VAR(void *__)) { }

static VALUE newobj_overhead(RB_UNUSED_VAR(VALUE _)) {
  VALUE tp = rb_tracepoint_new(0, RUBY_INTERNAL_EVENT_NEWOBJ, on_newobj_event, NULL);
  rb_tracepoint_enable(tp); rb_yield(Qnil); rb_tracepoint_disable(tp);
  return Qtrue;
}

void init_newobj_overhead(VALUE lowlevel_toolkit_module) {
  rb_define_singleton_method(lowlevel_toolkit_module, "newobj_overhead", newobj_overhead, 0);
}
