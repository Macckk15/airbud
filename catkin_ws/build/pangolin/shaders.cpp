#include <unordered_map>
#include <string>

namespace pangolin {
const std::unordered_map<std::string,const char*>& GetBuiltinShaders() {
	static const std::unordered_map<std::string,const char*> builtin_shaders = {
{ "/components/pango_opengl/shaders/colormaps.glsl.h",
 R"SHADER_SOURCE(
// From https://www.shadertoy.com/view/WlfXRN
vec3 plasma(float t) {
    const vec3 c0 = vec3(0.05873234392399702, 0.02333670892565664, 0.5433401826748754);
    const vec3 c1 = vec3(2.176514634195958, 0.2383834171260182, 0.7539604599784036);
    const vec3 c2 = vec3(-2.689460476458034, -7.455851135738909, 3.110799939717086);
    const vec3 c3 = vec3(6.130348345893603, 42.3461881477227, -28.51885465332158);
    const vec3 c4 = vec3(-11.10743619062271, -82.66631109428045, 60.13984767418263);
    const vec3 c5 = vec3(10.02306557647065, 71.41361770095349, -54.07218655560067);
    const vec3 c6 = vec3(-3.658713842777788, -22.93153465461149, 18.19190778539828);
    return c0+t*(c1+t*(c2+t*(c3+t*(c4+t*(c5+t*c6)))));
}
vec3 viridis(float t) {
    const vec3 c0 = vec3(0.2777273272234177, 0.005407344544966578, 0.3340998053353061);
    const vec3 c1 = vec3(0.1050930431085774, 1.404613529898575, 1.384590162594685);
    const vec3 c2 = vec3(-0.3308618287255563, 0.214847559468213, 0.09509516302823659);
    const vec3 c3 = vec3(-4.634230498983486, -5.799100973351585, -19.33244095627987);
    const vec3 c4 = vec3(6.228269936347081, 14.17993336680509, 56.69055260068105);
    const vec3 c5 = vec3(4.776384997670288, -13.74514537774601, -65.35303263337234);
    const vec3 c6 = vec3(-5.435455855934631, 4.645852612178535, 26.3124352495832);
    return c0+t*(c1+t*(c2+t*(c3+t*(c4+t*(c5+t*c6)))));
}
vec3 magma(float t) {
    const vec3 c0 = vec3(-0.002136485053939582, -0.000749655052795221, -0.005386127855323933);
    const vec3 c1 = vec3(0.2516605407371642, 0.6775232436837668, 2.494026599312351);
    const vec3 c2 = vec3(8.353717279216625, -3.577719514958484, 0.3144679030132573);
    const vec3 c3 = vec3(-27.66873308576866, 14.26473078096533, -13.64921318813922);
    const vec3 c4 = vec3(52.17613981234068, -27.94360607168351, 12.94416944238394);
    const vec3 c5 = vec3(-50.76852536473588, 29.04658282127291, 4.23415299384598);
    const vec3 c6 = vec3(18.65570506591883, -11.48977351997711, -5.601961508734096);
    return c0+t*(c1+t*(c2+t*(c3+t*(c4+t*(c5+t*c6)))));
}

vec3 inferno(float t) {
    const vec3 c0 = vec3(0.0002189403691192265, 0.001651004631001012, -0.01948089843709184);
    const vec3 c1 = vec3(0.1065134194856116, 0.5639564367884091, 3.932712388889277);
    const vec3 c2 = vec3(11.60249308247187, -3.972853965665698, -15.9423941062914);
    const vec3 c3 = vec3(-41.70399613139459, 17.43639888205313, 44.35414519872813);
    const vec3 c4 = vec3(77.162935699427, -33.40235894210092, -81.80730925738993);
    const vec3 c5 = vec3(-71.31942824499214, 32.62606426397723, 73.20951985803202);
    const vec3 c6 = vec3(25.13112622477341, -12.24266895238567, -23.07032500287172);
    return c0+t*(c1+t*(c2+t*(c3+t*(c4+t*(c5+t*c6)))));
}

// https://www.shadertoy.com/view/4dXXDX
// if edge0 < x <= edge1, return 1.0, otherwise return 0
float colormap_segment(float edge0, float edge1, float x)
{
    return step(edge0,x) * (1.0-step(edge1,x));
}
vec3 gray(float t)
{
    return vec3(t);
}
vec3 hot(float t)
{
    return vec3(smoothstep(0.00,0.33,t),
                smoothstep(0.33,0.66,t),
                smoothstep(0.66,1.00,t));
}
vec3 cool(float t)
{
    return mix( vec3(0.0,1.0,1.0), vec3(1.0,0.0,1.0), t);
}
vec3 autumn(float t)
{
    return mix( vec3(1.0,0.0,0.0), vec3(1.0,1.0,0.0), t);
}
vec3 winter(float t)
{
    return mix( vec3(0.0,0.0,1.0), vec3(0.0,1.0,0.5), sqrt(t));
}
vec3 spring(float t)
{
    return mix( vec3(1.0,0.0,1.0), vec3(1.0,1.0,0.0), t);
}
vec3 summer(float t)
{
    return mix( vec3(0.0,0.5,0.4), vec3(1.0,1.0,0.4), t);
}
vec3 ice(float t)
{
   return vec3(t, t, 1.0);
}
vec3 fire(float t)
{
    return mix( mix(vec3(1,1,1), vec3(1,1,0), t),
                mix(vec3(1,1,0), vec3(1,0,0), t*t), t);
}
vec3 ice_and_fire(float t)
{
    return colormap_segment(0.0,0.5,t) * ice(2.0*(t-0.0)) +
           colormap_segment(0.5,1.0,t) * fire(2.0*(t-0.5));
}
vec3 reds(float t)
{
    return mix(vec3(1,1,1), vec3(1,0,0), t);
}
vec3 greens(float t)
{
    return mix(vec3(1,1,1), vec3(0,1,0), t);
}
vec3 blues(float t)
{
    return mix(vec3(1,1,1), vec3(0,0,1), t);
}
// By Morgan McGuire
vec3 wheel(float t)
{
    return clamp(abs(fract(t + vec3(1.0, 2.0 / 3.0, 1.0 / 3.0)) * 6.0 - 3.0) -1.0, 0.0, 1.0);
}
// By Morgan McGuire
vec3 stripes(float t)
{
    return vec3(mod(floor(t * 64.0), 2.0) * 0.2 + 0.8);
}

vec3 Hsv(float hue, float sat, float val)
{
    float h = 6.0 * hue;
    int i = int(floor(h));
    float f = (i%2 == 0) ? 1-(h-i) : h-i;
    float m = val * (1-sat);
    float n = val * (1-sat*f);

    switch(i)
    {
    case 0: return vec3(val,n,m);
    case 1: return vec3(n,val,m);
    case 2: return vec3(m,val,n);
    case 3: return vec3(m,n,val);
    case 4: return vec3(n,m,val);
    case 5: return vec3(val,m,n);
    default:
        return vec3(0.0,0.0,0.0);
    }
}

vec3 GetColourBin(int i, float sat, float val)
{
    float hue = i * 0.5 * (3.0 - sqrt(5.0));
    hue = hue - floor(hue);
    return Hsv(hue,sat,val);
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/font.glsl.h",
 R"SHADER_SOURCE(
uniform sampler2D u_font_atlas;
uniform sampler2D u_font_offsets;

const float font_height = 32.0;

float screenPxRange(vec2 tex_coord) {
    const float pxRange = 2.0;
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_font_atlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(tex_coord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float sdf_font(vec4 atlas_offset, vec2 pos)
{
    float atlas_dim = textureSize(u_font_atlas, 0).x;

    vec2 p = vec2(1,-1) * clamp2(
        pos/atlas_dim, vec2(0.0, 0.0),
        vec2(atlas_offset.z, -atlas_offset.w)
    );

    vec2 uv = atlas_offset.xy + p;
    vec2 tex = vec2(uv.x, uv.y);
    vec3 msd = texture(u_font_atlas, tex).xyz;
    float sd = median(msd.r, msd.g, msd.b);
    return screenPxRange(tex)*(sd - 0.5);
}

float sdf_font(int char_id, vec2 pos )
{
    vec4 font_offset = texelFetch(u_font_offsets, ivec2(char_id, 0), 0);
    vec2 screen_offset = texelFetch(u_font_offsets, ivec2(char_id, 1), 0).xy;
    return sdf_font(font_offset, pos - vec2(font_height/2.0) - screen_offset*font_height);
}

float font_color(vec4 atlas_offset, vec2 pos )
{
    return clamp(sdf_font(atlas_offset, pos) + 0.5, 0.0, 1.0);
}

float font_color(int char_id, vec2 pos )
{
    return clamp(sdf_font(char_id, pos) + 0.5, 0.0, 1.0);
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/main_experiments.glsl",
 R"SHADER_SOURCE(
@start vertex
#version 150 core

in vec3 a_position;
out vec2 v_pos;
uniform mat4 u_T_cm;

void main() {
    gl_Position = u_T_cm * vec4(a_position, 1.0);
    v_pos = a_position.xy;
}

@start fragment
#version 150 core
#include "utils.glsl.h"
#include "colormaps.glsl.h"
#include "sdf.glsl.h"
#include "font.glsl.h"

in vec2 v_pos;
out vec4 FragColor;
uniform float u_val;
uniform vec2 u_mouse_pos;
uniform int u_char_id;
uniform usampler2D u_text;

const vec2 light_dir = vec2(-sqrt(0.5), -sqrt(0.5));
const float M_PI = 3.1415926535897932384626433832795;

vec2 wave(float x, float center, float rad)
{
    float phase = clamp( (x - center) / rad, -1.0, 1.0);
    float y = (1+cos(phase*M_PI))/2.0;
    float dy_dx = -0.5*M_PI*sin(phase*M_PI)/rad;
    return vec2(y, dy_dx);
}

vec4 slider_wave() {
    float half_height = 25.0;
    float padding = 15.0;
    float rad = 50.0;
    float height = 40.0;
    float width = 400.0;
    float val_pix = u_val*width;
    float circ_rad = 5;

    vec2 p = vec2(v_pos.x, mod(v_pos.y, 2*(padding+half_height) ) );
    vec2 xy = p - vec2(padding);
    vec2 y_dy = height * wave(xy.x, val_pix, rad);

    // distance to wave
    float dist_wave = abs(xy.y - y_dy.x) / sqrt(1.0 + y_dy.y*y_dy.y);
    if(xy.x < 0.0 || xy.x > width) dist_wave = 1e6;

    // distance to start circle
    float dist_c1 = length(xy - vec2(0.0,height*wave(0.0, val_pix, rad).x )) - circ_rad;

    // distance to end circle
    float dist_c2 = length(xy - vec2(width,height*wave(width, val_pix, rad).x )) - circ_rad;

    float de = min(min(dist_wave, dist_c1), dist_c2);

    vec3 v = mix( vec3(0.9), vec3(1.0,0.6,0.2), 1.0-smoothstep( 3.0, 4.0, de ) );

    return vec4(v,1.0);
}

vec4 slider(bool button)
{
    // dimensions
    float padding = 15.0;
    float half_width = 200.0;
    float half_height = 25.0;

    // Style params
    float slider_outline_border = 2;
    float boss_border = 1;
    float boss_radius = 25;

    vec3 color_panel = vec3(0.8);
    vec3 color_boss_base = color_panel;
    vec3 color_boss_diff = vec3(0.2, 0.15, 0.20);
    vec3 color_slider = vec3(0.9, 0.7, 0.7);
    vec3 color_slider_outline = color_slider - vec3(0.1);

//    // Style params
//    float half_height = 35.0;
//    float boss_border = 3;
//    float boss_radius = 35;
//    float slider_outline_border = 4;

//    vec3 color_panel = vec3(0.95);
//    vec3 color_boss_base = vec3(0.0);
//    vec3 color_boss_diff = vec3(0, 0, 0);
//    vec3 color_slider = vec3(0.7, 0.7, 0.7);
//    vec3 color_slider_outline = vec3(0.95);

    // maths
    float val_pix = u_val*2.0*half_width;
    float frac_y = mod(v_pos.y, 2*(padding+half_height) );
    vec2 p = vec2(v_pos.x, frac_y );
    float pos_along_slider = clamp((p.x-padding) / val_pix, 0.0, 1.0);

    float panel_sdf = sdf_rounded_rect(v_pos, vec2(half_width+padding, 15*half_height), vec2(half_width+2*padding, 15*(half_height+padding)), boss_radius);
    float box_sdf   = sdf_rounded_rect(p, vec2(padding+half_width, padding+half_height), vec2(half_width, half_height), boss_radius);
    vec2  box_grad = normalize(vec2(dFdx(box_sdf), dFdy(box_sdf)) + vec2(0.0001, 0.0001)); // (eps to avoid bad normalization)
    float slide_sdf = sdf_rounded_rect(p, vec2(padding+val_pix/2.0, padding+half_height), vec2(val_pix/2.0, half_height), boss_radius);
    vec2  slide_grad = normalize(vec2(dFdx(slide_sdf), dFdy(slide_sdf)));

    bool pressed = button && ((u_char_id % 2) == 0);

    // Panel
    vec4 v = color_sdf(panel_sdf, color_panel);

    if(pressed) box_grad*= -1;
    vec3 color_boss = color_boss_base + dot(box_grad,light_dir) * color_boss_diff;

    // Add indented (embossed) area for slider / button
    v = composite( color_sdf(box_sdf, color_panel, color_boss, boss_border ), v);

    if(!button) {
        // Add Slider with outline
        v = composite( color_sdf(slide_sdf+boss_border, color_slider, color_slider_outline, slider_outline_border ), v);
    }

    // Add text
    vec2 font_pos   = 1.5*p - vec2(50.0, padding + half_height + 10 );
    int font_i = int(font_pos.x / 20.0);
    font_pos.x = font_pos.x >= 0.0 ? mod(font_pos.x, 20.0) : -1;

    if(0.0 <= font_pos.x && 0 <= font_i && font_i < 10) {
        uint char_id = texelFetch(u_text, ivec2(font_i, 0), 0).r;
        if(0u < char_id) {
            float font_opacity = font_color(int(char_id), font_pos);
            v = composite(vec4(vec3(0.0),font_opacity), v);
        }
    }

    return v;
}

vec4 font_render() {
    const float padding = 15.0;
    float opacity = font_color(u_char_id, 1.5*v_pos - vec2(10,padding+25+10));
    return vec4(vec3(0.0),opacity);
}

void main() {
    FragColor = slider(false);
//    FragColor = slider_wave();
//    FragColor = font_render();
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/main_text.glsl",
 R"SHADER_SOURCE(
@start vertex
#version 150 core

in vec3 a_position;
in uint a_char_index;
out vec3 pos;
out uint index;

void main() {
    pos = a_position;
    index = a_char_index;
}

@start geometry
#version 150 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 u_T_cm;

in vec3 pos[];
in uint index[];
out vec2 v_pos;
out vec2 v_win;
flat out uint char_id;

const bool flip_y = true;

uniform float u_scale;

void main() {
    float w = u_scale * 32.0;
    float h = u_scale * 32.0;

    float expand = 0.0;

//    vec2 corners[4] = vec2[](
//        vec2(0.0,0.0), vec2(w,0.0),
//        vec2(0.0,h), vec2(w,h)
//    );
    vec2 corners[4] = vec2[](
        vec2(-expand,-expand), vec2(w+expand,-expand),
        vec2(-expand,h+expand), vec2(w+expand,h+expand)
    );

    char_id = index[0];

    for(uint i=0u; i < 4u;  ++i) {
        v_win = pos[0].xy + corners[i];
        v_pos = corners[i];
        if(flip_y) v_pos.y = h - v_pos.y;
        gl_Position = u_T_cm * vec4(v_win, pos[0].z, 1.0);
        EmitVertex();
    }

    EndPrimitive();}

@start fragment
#version 150 core
#include "utils.glsl.h"
#include "sdf.glsl.h"
#include "font.glsl.h"

in vec2  v_pos;
flat in uint   char_id;
out vec4 FragColor;

uniform float u_scale;

void main() {
    vec2 pos = v_pos / u_scale - vec2(0,8);
    float sdf = sdf_font(int(char_id), pos);
    float opacity = clamp( sdf + 0.5, 0.0, 1.0);
    FragColor = vec4( vec3(0.0), opacity );
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/main_widgets.glsl",
 R"SHADER_SOURCE(
@start vertex
#version 150 core

in vec4 a_position;
out vec4 pos;

void main() {
    pos = a_position;
}

@start geometry
#version 150 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 u_T_cm;
uniform float u_width;
uniform float u_height;
uniform int u_selected_index;

in vec4 pos[];
out vec2 v_pos;
out vec2 v_win;
flat out float divisions;
flat out float val;
flat out int  selected_index;
flat out int  widget_index;
flat out uint  widget_type;


void output_widget()
{
    divisions = floor(pos[0].z);
    val = 2.0*(pos[0].z - divisions);

    widget_type = uint(pos[0].w);
    selected_index = u_selected_index;
    widget_index = int(pos[0].y);

    vec2 corners[4] = vec2[](
        vec2(0.0,0.0), vec2(u_width,0.0),
        vec2(0.0,u_height), vec2(u_width,u_height)
    );

    for(uint i=0u; i < 4u;  ++i) {
        v_win = vec2(0.0, u_height*pos[0].y) + corners[i];
        v_pos = corners[i];
        gl_Position = u_T_cm * vec4(v_win, 0.0, 1.0);
        EmitVertex();
    }

    EndPrimitive();
}

void main() {
    output_widget();
}

@start fragment
#version 150 core
#include "utils.glsl.h"
#include "colormaps.glsl.h"
#include "sdf.glsl.h"

in vec2 v_pos;
in vec2 v_win;
flat in float  divisions;
flat in float val;
flat in uint  widget_type;
flat in int  selected_index;
flat in int  widget_index;
out vec4 FragColor;

// Dimensions
uniform float u_width;
uniform float u_height;
uniform float u_padding;
uniform int u_num_widgets;

// Style params
uniform float slider_outline_border;
uniform float boss_border;
uniform float boss_radius_factor;

uniform vec3 color_panel;
uniform vec3 color_boss_base;
uniform vec3 color_boss_diff;
uniform vec3 color_slider;
uniform vec3 color_slider_outline;

const vec2 light_dir = vec2(-sqrt(0.5), -sqrt(0.5));
const float M_PI = 3.1415926535897932384626433832795;

float padding = u_padding;
float half_width = u_width/2.0 - padding;
float half_height = u_height/2.0 - padding;
float boss_radius = half_height * boss_radius_factor;

vec4 widget_panel(vec2 v_win)
{
    vec3 color_panel_border = vec3(0.9);
    float border_panel = 3;

    float panel_sdf = sdf_rounded_rect(v_win, vec2(half_width+padding, u_num_widgets*(half_height+padding)), vec2(half_width+padding, u_num_widgets*(half_height+padding)), boss_radius);
    return color_sdf(panel_sdf, color_panel, color_panel_border, border_panel);
}

vec4 widget_seperator()
{
    float line_sdf  = sdf_line_segment(v_pos, vec2(2*padding,2.2*half_height), vec2(u_width-2*padding, 2.2*half_height));
    vec4 v = widget_panel(v_win);
    v = composite( color_sdf(line_sdf-1, vec3(0.7)), v);
    return v;
}

vec4 widget()
{
    // widget_type:
    // 0: Label
    // 1: Textbox
    // 2: button
    // 3: checkbox
    // 4: slider
    // 5: seperator

    bool is_textbox   = widget_type==1u;
    bool is_button    = widget_type==2u || widget_type==3u;
    bool is_slider    = widget_type==4u;
    bool is_seperator = widget_type==5u;

    bool is_toggled  = val > 0.5;
    bool is_active_widget = selected_index == widget_index;

    if(is_seperator) return widget_seperator();

    // dimensions
    float padding = u_padding;
    float half_width = u_width/2.0 - padding;
    float half_height = u_height/2.0 - padding;
    float boss_radius = half_height * boss_radius_factor;

    // maths
    float val_pix = val*2.0*half_width;

    float slider_center = padding+val_pix/2.0;
    float slider_width  = val_pix/2.0;
    vec3 color_inside = color_slider;
    vec3 color_inside_outline = color_slider_outline;
    float border_inside = slider_outline_border;
    float inside_height = half_height;
    float inside_radius = half_height;

    if(is_button) {
        slider_center = 2*half_width-half_height;
        slider_width = half_height+padding;
        color_inside_outline = color_slider_outline;
        color_inside = is_toggled ? vec3(0.9,0.8,0.8): vec3(0.8);
        border_inside = 2;
        slider_width -= 4;
        inside_height -= 4;
        inside_radius -= 4;
    }

    float box_sdf   = sdf_rounded_rect(v_pos, vec2(padding+half_width, padding+half_height), vec2(half_width, half_height), boss_radius);
    vec2  box_grad = normalize(vec2(dFdx(box_sdf), dFdy(box_sdf)) + vec2(0.0001, 0.0001)); // (eps to avoid bad normalization)
    float slide_sdf = sdf_rounded_rect(v_pos, vec2(slider_center, padding+half_height), vec2(slider_width, inside_height), inside_radius);

    // Panel
    vec4 v = widget_panel(v_win);

    if(is_button || is_slider || is_textbox) {
        vec3 color_boss = color_boss_base - /*dot(box_grad,light_dir) **/ color_boss_diff;
        float border = boss_border;
        if(is_active_widget) {
            color_boss.x += .3;
            border += 1;
        }

        if(is_textbox) {
            v = composite( color_sdf(box_sdf, vec3(0.9), color_boss, border ), v);
        }else{
            // Add indented (embossed) area for slider / button
            v = composite( color_sdf(box_sdf, color_panel, color_boss, border ), v);
        }
    }

    if(is_button || is_slider) {
        // Add Slider with outline
        v = composite( color_sdf(slide_sdf+boss_border, color_inside, color_inside_outline, border_inside ), v);
    }

    // WIP: markings
    if(is_slider) {
        float val_here = divisions * (v_pos.x-padding) / (2.0*(u_width/2.0 - padding));
        float val_closest = round(val_here);
        float msdf = mod(abs(val_closest-val_here),1.0);
        float alpha = 1.0 - smoothstep(0.0, 1.0, box_sdf);
        float dist_scale = half_width / divisions;
        vec4 c = color_sdf(dist_scale*msdf, color_inside_outline);
        c.a *= alpha;
        v = composite( c, v);
    }

    return v;
}

void main() {
    FragColor = widget();
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/matcap.glsl.h",
 R"SHADER_SOURCE(
uniform sampler2D u_matcap;

vec3 matcap(vec3 normal)
{
    vec2 t = (normal.xy + vec2(1.0,1.0)) / 2.0;
    return texture(u_matcap, t).xyz;
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/noise.glsl.h",
 R"SHADER_SOURCE(
vec2 grid_noise( ivec2 z )  // replace this anything that returns a random vector
{
    // 2D to 1D  (feel free to replace by some other)
    int n = z.x+z.y*11111;

    // Hugo Elias hash (feel free to replace by another one)
    n = (n<<13)^n;
    n = (n*(n*n*15731+789221)+1376312589)>>16;

    // Perlin style vectors
    n &= 7;
    vec2 gr = vec2(n&1,n>>1)*2.0-1.0;
    return ( n>=6 ) ? vec2(0.0,gr.x) :
           ( n>=4 ) ? vec2(gr.x,0.0) :
                              gr;
}

float perlin_noise( in vec2 p )
{
    ivec2 i = ivec2(floor( p ));
     vec2 f =       fract( p );

    vec2 u = f*f*(3.0-2.0*f); // feel free to replace by a quintic smoothstep instead

    return mix( mix( dot( grid_noise( i+ivec2(0,0) ), f-vec2(0.0,0.0) ),
                     dot( grid_noise( i+ivec2(1,0) ), f-vec2(1.0,0.0) ), u.x),
                mix( dot( grid_noise( i+ivec2(0,1) ), f-vec2(0.0,1.0) ),
                     dot( grid_noise( i+ivec2(1,1) ), f-vec2(1.0,1.0) ), u.x), u.y);
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/sdf.glsl.h",
 R"SHADER_SOURCE(
float sdf_circ(vec2 p, vec2 center, float rad)
{
    float dist = length(p - center);
    return dist - rad;
}

float sdf_rect(vec2 p, vec2 center, vec2 half_size) {
  vec2 d = abs(p - center) - half_size;
  float outside = length(max(d, 0.));
  float inside = min(max(d.x, d.y), 0.);
  return outside + inside;
}

float sdf_rounded_rect(vec2 p, vec2 center, vec2 half_size, float rad) {
    return sdf_rect(p,center,half_size-vec2(rad)) - rad;
}

float sdf_rect_extent(vec2 p, vec2 corner1, vec2 corner2) {
    vec2 center = (corner1 + corner2) / 2.0;
    vec2 half_size = abs(corner2 - corner1) / 2.0;
    return sdf_rect(p, center, half_size );
}

float sdf_rounded_rect_extent(vec2 p, vec2 corner1, vec2 corner2, float rad) {
    vec2 center = (corner1 + corner2) / 2.0;
    vec2 half_size = abs(corner2 - corner1) / 2.0;
    return sdf_rect(p,center,half_size-vec2(rad)) - rad;
}

float sdf_line_segment(vec2 p, vec2 a, vec2 b) {
    vec2 ba = b - a;
    vec2 pa = p - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.);
    return length(pa - h * ba);
}

float sdf_grid(vec2 p, vec2 spacing)
{
  vec2 half_space = spacing / 2.0;
  vec2 dist2 = mod(p + half_space, spacing) - half_space;
  return length(dist2);
}

float sdf_grid(vec2 p_in, vec2 spacing, vec2 origin, ivec2 grid_size)
{
  vec2 p = p_in - origin;
  vec2 half_space = spacing / 2.0;
  vec2 dist2 = mod(p + half_space, spacing) - half_space;
  ivec2 n = ivec2( (p / spacing) - 0.5);
  if( all(lessThanEqual(ivec2(0,0),n)) && all(lessThan(n,grid_size)) ) {
    return length(dist2);
  }else{
    return 0.0/0.0;
  }
}

float opacity(float sdf)
{
    return clamp(-sdf + 0.5, 0.0, 1.0);
}

vec4 color_sdf(float sdf, vec3 color_inside)
{
    return vec4(color_inside, smoothstep(-0.5, 0.5, -sdf));
}

vec4 color_sdf(float sdf, vec4 color_inside)
{
    return vec4(color_inside.xyz, color_inside.w * smoothstep(-0.5, 0.5, -sdf));
}

vec3 transition(vec3 a, vec3 b, float point, float x)
{
    float s = smoothstep(point-0.5, point+0.5, x);
    return (1.0-s)*a + s*b;
}

// Border encroaches toward interior
vec4 color_sdf(float sdf, vec3 color_inside, vec3 color_border, float border_size)
{
    return vec4(
        transition(color_inside, color_border, -border_size, sdf),
        smoothstep(-0.5, 0.5, -sdf)
    );
}
)SHADER_SOURCE" },
{ "/components/pango_opengl/shaders/utils.glsl.h",
 R"SHADER_SOURCE(
float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

vec2 clamp2(vec2 v, vec2 low, vec2 high)
{
    return vec2(
        clamp(v.x, low.x, high.x),
        clamp(v.y, low.y, high.y)
    );
}

vec4 composite(vec4 top_layer, vec4 bottom_layer)
{
    float alpha = top_layer.a;
//    return alpha * top_layer + (1.0 - alpha) * bottom_layer;
    return vec4(alpha * top_layer.xyz + (1.0 - alpha) * bottom_layer.xyz, max(alpha,bottom_layer.a));
}
)SHADER_SOURCE" },
	};
	return builtin_shaders;
}
}
