#include <ruby/ruby.h>
#include <ruby/debug.h>

static VALUE callback(const rb_debug_inspector_t *dbg_context, void *return_self) {
  return (return_self != NULL) ?
    // Depth: 0 -> us; 1 -> caller; 2 -> caller of caller
    rb_debug_inspector_frame_self_get(dbg_context, 2) :
    rb_debug_inspector_frame_binding_get(dbg_context, 2);
}

static VALUE who_called_me(RB_UNUSED_VAR(VALUE _)) { return rb_debug_inspector_open(callback, (void *) !NULL); }
static VALUE who_called_me_binding(RB_UNUSED_VAR(VALUE _)) { return rb_debug_inspector_open(callback, NULL); }

void init_who_called_me(VALUE lowlevel_toolkit_module) {
  rb_define_singleton_method(lowlevel_toolkit_module, "who_called_me", who_called_me, 0);
  rb_define_singleton_method(lowlevel_toolkit_module, "who_called_me_binding", who_called_me_binding, 0);
}
