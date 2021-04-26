#include "MaterialTextura.h"
MaterialTextura::MaterialTextura(vec3 a, vec3 d, vec3 s, float beta, shared_ptr<Texture> texture): Material(a,d,s,vec3(0,0,0),beta)
{
    this->texture = texture;
}

vec3 MaterialTextura::getDiffuse(vec2 point)const{
    return texture->getColorPixel(point);
}

vec3 MaterialTextura::getAmbient(vec2 point)const{
    return texture->getColorPixel(point);
}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    //color = getDiffuse(rec.uv);
    return false;
}
