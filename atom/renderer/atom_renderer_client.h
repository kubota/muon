// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_RENDERER_ATOM_RENDERER_CLIENT_H_
#define ATOM_RENDERER_ATOM_RENDERER_CLIENT_H_

#include <string>
#include <vector>

#include "atom/common/options_switches.h"
#include "base/command_line.h"
#include "content/public/renderer/content_renderer_client.h"

namespace extensions {
class Dispatcher;
}

namespace atom {

class AtomBindings;
class NodeBindings;
class JavascriptBindings;

class AtomRendererClient : public content::ContentRendererClient {
 public:
  AtomRendererClient();
  virtual ~AtomRendererClient();

  void DidCreateScriptContext(v8::Handle<v8::Context> context);
  void WillReleaseScriptContext(v8::Handle<v8::Context> context);
 private:
  enum NodeIntegration {
    ALL,
    EXCEPT_IFRAME,
    MANUAL_ENABLE_IFRAME,
    DISABLE,
  };

  // content::ContentRendererClient:
  void RenderThreadStarted() override;
  void RenderFrameCreated(content::RenderFrame*) override;
  void RenderViewCreated(content::RenderView*) override;
  void RunScriptsAtDocumentStart(content::RenderFrame* render_frame) override;
  blink::WebSpeechSynthesizer* OverrideSpeechSynthesizer(
      blink::WebSpeechSynthesizerClient* client) override;
  bool OverrideCreatePlugin(content::RenderFrame* render_frame,
                            blink::WebLocalFrame* frame,
                            const blink::WebPluginParams& params,
                            blink::WebPlugin** plugin) override;
  bool AllowPopup() override;
  bool ShouldFork(blink::WebLocalFrame* frame,
                  const GURL& url,
                  const std::string& http_method,
                  bool is_initial_navigation,
                  bool is_server_redirect,
                  bool* send_referrer) override;
  content::BrowserPluginDelegate* CreateBrowserPluginDelegate(
      content::RenderFrame* render_frame,
      const std::string& mime_type,
      const GURL& original_url) override;
  void AddKeySystems(std::vector<media::KeySystemInfo>* key_systems) override;
  void GetNavigationErrorStrings(content::RenderFrame* render_frame,
                                 const blink::WebURLRequest& failed_request,
                                 const blink::WebURLError& error,
                                 std::string* error_html,
                                 base::string16* error_description) override;
  void DidInitializeServiceWorkerContextOnWorkerThread(
      v8::Local<v8::Context> context,
      const GURL& url) override;
  void WillDestroyServiceWorkerContextOnWorkerThread(
      v8::Local<v8::Context> context,
      const GURL& url) override;

  bool WillSendRequest(
    blink::WebFrame* frame,
    ui::PageTransition transition_type,
    const GURL& url,
    const GURL& first_party_for_cookies,
    GURL* new_url) override;

  std::unique_ptr<NodeBindings> node_bindings_;
  std::unique_ptr<AtomBindings> atom_bindings_;

  DISALLOW_COPY_AND_ASSIGN(AtomRendererClient);
};

}  // namespace atom

#endif  // ATOM_RENDERER_ATOM_RENDERER_CLIENT_H_
