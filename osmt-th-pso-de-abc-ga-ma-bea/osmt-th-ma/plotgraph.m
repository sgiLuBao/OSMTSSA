inputfile='input8.txt';
fidpro=fopen(inputfile,'r');
vertice=fscanf(fidpro,'%d',1);      %点数
graph=ones(vertice,2);
particle = ones(1,3*vertice-3);
for i=1:vertice
    graph(i,1)=fscanf(fidpro,'%f',1);%横坐标
    graph(i,2)=fscanf(fidpro,'%f',1);%纵坐标
end
for i=1:vertice
    plot(graph(i,1),graph(i,2),'r.');
    x=graph(i,1);
    y=graph(i,2);
    str=strcat('. ',num2str(i),'.','(',num2str(x),',',num2str(y),')');
    text(graph(i,1),graph(i,2),str);
    hold on;
end
a=[0,10000,0,10000];
axis(a);