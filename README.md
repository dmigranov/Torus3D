# SphEll3D

A library for visualizing scenes in three-dimensional spherical and elliptical spaces. Created using the Direct3D 11 API and the [DirectX Tool Kit](https://github.com/microsoft/DirectXTK).

You can add meshes to the spaces and apply textures to them. You can also add parent meshes and add updaters so that meshes' positions on the scene will be updated.

GameExample is an example project built with the library.

# Some images and GIFs

<p align="center">
<img src="/fig1.png">
<i>Demonstration of fog effect and geometrical and optical properties of the three-dimensional elliptic space; the eight objects pictured are actually same-sized, their apparent size changes differently compared to the ordinary Euclidean space.</i>
</p>

<br/>


<p align="center">
<img src="/rotating-object.gif">
</p>
<p align="center">
<i>The spectator is standing on the surface of the "Earth"; due to the behaviour of geodesics forming their "viewing cone", the viewer sees not only the points in the bottom part of the picture (like it would be in the Euclidean space) but also ones in the top part of the picture (they are antipodes of the Earth's points that are visible in the bottom part), which are less contrast because of the fog effect. A cube is rotating and changing in size.</i>
</p>

<br/>


<p align="center">
<img src="/optics.gif">
</p>
<p align="center">
<i>Another demonstration of optics in the spherical space: first the small sphere is just in front of the camera; then it moves forward and now the small sphere is behind the camera, but the spectator still sees it, reflected horizontally and vertically (thus giving a rotation)!</i>
</p>

<br/>


<p align="center">
<img src="/movement_sph.gif">
</p>
<p align="center">
<i>Movement in spherical space. Change of apparent sizes depending on distance between the observer and the object. </i>
</p>

<br/>

<p align="center">
<img src="/movement_ell.gif">
</p>
<p align="center">
<i>Movement in elliptical space. The elliptical space can be seen as the spherical space with its antipodal points identified; thus, its volume is two times less. That's the reason for the fog effect looking different compared to the spherical case.</i>
</p>

