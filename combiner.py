import re
import os
import argparse

def combine_web_to_header(html_path, css_path, js_path, cpp_header_path, is_module=False):
    # 1. Check if input files exist
    for path in [html_path, css_path, js_path]:
        if not os.path.exists(path):
            print(f"Error: Could not find '{path}'")
            return

    # Ensure output directory exists before writing
    output_dir = os.path.dirname(cpp_header_path)
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)

    # 2. Read contents of all three files
    with open(html_path, 'r', encoding='utf-8') as file:
        html_content = file.read()
        
    with open(css_path, 'r', encoding='utf-8') as file:
        css_content = file.read()
        
    with open(js_path, 'r', encoding='utf-8') as file:
        js_content = file.read()

    # Extract base filenames so the regex finds the correct tags dynamically 
    css_filename = os.path.basename(css_path)
    js_filename = os.path.basename(js_path)

    # 3. Replace CSS <link> tag for the specific CSS file with a <style> block
    css_pattern = re.compile(rf'<link[^>]*href=["\'](?:.*?/)?{re.escape(css_filename)}["\'][^>]*>', re.IGNORECASE)
    style_block = f"<style>\n{css_content}\n</style>"
    html_content = css_pattern.sub(lambda _: style_block, html_content, count=1)

    # 4. Remove ONLY the local script tag matching the JS filename
    js_pattern = re.compile(rf'<script[^>]*src=["\'](?:\./)?{re.escape(js_filename)}["\'][^>]*>[\s\S]*?</script>', re.IGNORECASE)
    html_content = js_pattern.sub('', html_content)

    # 5. Inject inline JS before closing </body> tag
    script_type = ' type="module"' if is_module else ''
    script_block = f'<script{script_type}>\n{js_content}\n</script>\n</body>'
    html_content = re.sub(r'(?i)</body>', lambda _: script_block, html_content)

    # Dynamically generate C++ macros and variable names based on the output filename
    # e.g., "home.h" -> HOME_H and home_html
    base_name = os.path.splitext(os.path.basename(cpp_header_path))[0]
    macro_name = f"{base_name.upper()}_H"
    var_name = f"{base_name}_html"

    # 6. Generate C++ Header File (.h) with Arduino.h included
    cpp_header_content = f"""#ifndef {macro_name}
#define {macro_name}

#include <Arduino.h>

const char {var_name}[] PROGMEM = R"rawliteral(
{html_content}
)rawliteral";

#endif // {macro_name}
"""
    # 7. Write to the C++ Header file (Overwrites if exists)
    with open(cpp_header_path, 'w', encoding='utf-8') as file:
        file.write(cpp_header_content)
        
    print(f"Success! C++ header file saved to: {cpp_header_path} (Module: {is_module})")


if __name__ == "__main__":
    # Process Home Page (Loads JS as a Module)
    combine_web_to_header(
        html_path="./web/home.html",
        css_path="./web/home.css",
        js_path="./web/home.js",
        cpp_header_path="./src/home.h",
        is_module=True
    )

    # Process Compendium Page (Loads JS as a standard Script)
    combine_web_to_header(
        html_path="./web/compendium.html",
        css_path="./web/compendium.css",
        js_path="./web/compendium.js",
        cpp_header_path="./src/compendium.h",
        is_module=False
    )