#ifndef MASTERDREZMANEJOXML
#define MASTERDREZMANEJOXML

/**
    * Devuelve el mensaje del diccionario de mensajes, de acuerdo al idioma
  *actual
    *
    * @param pParent
    * @param identificador
    */
const char *get_errorm(tinyxml2::XMLNode *pParent, const char *identificador) {

  if (!pParent)
    return NULL;

  pParent = pParent->FirstChildElement("errores");

  tinyxml2::XMLNode *pChild = pParent->FirstChildElement(identificador);
  if (!pChild)
    return NULL;

  tinyxml2::XMLElement *pElement = pChild->ToElement();
  if (pElement)
    return pElement->GetText();
  else
    return NULL;
}

/**
* Devuelve el mensaje del diccionario de mensajes, de acuerdo al idioma
*actual.
* Facilita el uso de la funcion get_errorm()
*
* @param currentlanguage
* @param identificador
*/ const char *get_message(int currentlanguage, const char *identificador) {
  return get_errorm(&doclang[currentlanguage], identificador);
}

#endif // MASTERDREZMANEJOXML
