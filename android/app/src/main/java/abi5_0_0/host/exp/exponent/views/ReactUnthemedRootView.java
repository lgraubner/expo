package abi5_0_0.host.exp.exponent.views;

import android.content.Context;
import android.view.ContextThemeWrapper;

import abi5_0_0.com.facebook.react.ReactRootView;
import host.exp.exponent.R;

public class ReactUnthemedRootView extends ReactRootView {
  public ReactUnthemedRootView(Context context) {
    super(new ContextThemeWrapper(
        context,
        R.style.Theme_Exponent_None
    ));
  }
}
