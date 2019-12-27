<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.3.1" name="terrain" tilewidth="32" tileheight="32" tilecount="1024" columns="32">
 <image source="../../img/terrain.png" width="1024" height="1024"/>
 <tile id="0">
  <animation>
   <frame tileid="876" duration="1000"/>
   <frame tileid="875" duration="1000"/>
   <frame tileid="874" duration="1000"/>
  </animation>
 </tile>
 <tile id="177">
  <animation>
   <frame tileid="177" duration="2500"/>
   <frame tileid="176" duration="2500"/>
   <frame tileid="175" duration="2500"/>
  </animation>
 </tile>
 <tile id="189">
  <animation>
   <frame tileid="187" duration="1000"/>
   <frame tileid="188" duration="1000"/>
   <frame tileid="189" duration="1000"/>
  </animation>
 </tile>
 <tile id="561">
  <animation>
   <frame tileid="561" duration="1000"/>
   <frame tileid="560" duration="1000"/>
   <frame tileid="559" duration="1000"/>
  </animation>
 </tile>
 <tile id="945" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="946" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="949" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="950" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="977" type="Object">
  <properties>
   <property name="blocked" type="bool" value="true"/>
   <property name="depth" type="int" value="5"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="hitbox" x="7" y="0" width="25" height="20"/>
  </objectgroup>
 </tile>
 <tile id="978" type="Object">
  <properties>
   <property name="blocked" type="bool" value="true"/>
   <property name="depth" type="int" value="5"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="hitbox" x="0" y="0" width="20" height="18"/>
  </objectgroup>
 </tile>
 <tile id="981" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="982" type="Object">
  <properties>
   <property name="depth" type="int" value="6"/>
  </properties>
 </tile>
 <tile id="1013" type="Object">
  <properties>
   <property name="blocked" type="bool" value="true"/>
   <property name="depth" type="int" value="5"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="hitbox" x="7" y="0" width="25" height="23"/>
  </objectgroup>
 </tile>
 <tile id="1014" type="Object">
  <properties>
   <property name="blocked" type="bool" value="true"/>
   <property name="depth" type="int" value="5"/>
  </properties>
  <objectgroup draworder="index" id="3">
   <object id="3" name="hitbox" x="0" y="0" width="20" height="25"/>
  </objectgroup>
 </tile>
</tileset>
