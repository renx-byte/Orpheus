import re
import os
import argparse

def combine_web_to_header(html_path, css_path, js_path, cpp_header_path):
    # 1. Check if input files exist
    for path in [html_path, css_path, js_path]:
        if not os.path.exists(path):
            print(f"Error: Could not find '{path}'")
            return

    # Ensure output directory exists before writing
    os.makedirs(os.path.dirname(cpp_header_path), exist_ok=True)

    # 2. Read contents of all three files
    with open(html_path, 'r', encoding='utf-8') as file:
        html_content = file.read()
        
    with open(css_path, 'r', encoding='utf-8') as file:
        css_content = file.read()
        
    with open(js_path, 'r', encoding='utf-8') as file:
        js_content = file.read()

    # 3. Replace CSS <link> tag with a <style> block
    css_pattern = re.compile(r'<link[^>]*rel=["\']stylesheet["\'][^>]*>')
    style_block = f"<style>\n{css_content}\n</style>"
    html_content = css_pattern.sub(lambda _: style_block, html_content, count=1)

    # 4. Remove external JS <script> tag from the <head>
    js_pattern = re.compile(r'<script[^>]*src=["\'][^"\']+["\'][^>]*>[\s\S]*?</script>')
    html_content = js_pattern.sub('', html_content)

    # 5. Inject inline JS before closing </body> tag
    script_block = f"<script>\n{js_content}\n</script>\n</body>"
    html_content = re.sub(r'(?i)</body>', lambda _: script_block, html_content)

    # 6. Generate C++ Header File (.h) with Arduino.h included
    cpp_header_content = f"""#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
{html_content}
)rawliteral";

#endif // INDEX_HTML_H
"""
    # 7. Write to the C++ Header file (Overwrites if exists)
    with open(cpp_header_path, 'w', encoding='utf-8') as file:
        file.write(cpp_header_content)
        
    print(f"Success! C++ header file saved to: {cpp_header_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Combine web files directly into a C++ header file.")
    parser.add_argument("--html", default="./web/index.html", help="Input HTML file")
    parser.add_argument("--css", default="./web/styles.css", help="Input CSS file")
    parser.add_argument("--js", default="./web/index.js", help="Input JS file")
    parser.add_argument("--cpp", default="./src/index_html.h", help="Output C++ Header file")
    
    args = parser.parse_args()
    combine_web_to_header(args.html, args.css, args.js, args.cpp)