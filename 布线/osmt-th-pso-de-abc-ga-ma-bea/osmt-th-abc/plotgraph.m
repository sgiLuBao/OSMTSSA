inputfile='rc02.txt';
fidpro=fopen(inputfile,'r');
vertice=fscanf(fidpro,'%d',1);      %����
graph=ones(vertice,2);
particle = ones(1,3*vertice-3);
for i=1:vertice
    graph(i,1)=fscanf(fidpro,'%f',1);%������
    graph(i,2)=fscanf(fidpro,'%f',1);%������
end
obstacle=fscanf(fidpro,'%d',1);      %����
Rectangle=ones(obstacle,4);
for i=1:obstacle
    Rectangle(i,1)=fscanf(fidpro,'%f',1);%���º�����
    Rectangle(i,2)=fscanf(fidpro,'%f',1);%����������
    Rectangle(i,3)=fscanf(fidpro,'%f',1);%���Ϻ�����
    Rectangle(i,4)=fscanf(fidpro,'%f',1);%����������
end
for i=1:vertice
    plot(graph(i,1),graph(i,2),'r.');
    x=graph(i,1);
    y=graph(i,2);
%     str=strcat(num2str(i),'.','(',num2str(x),',',num2str(y),')');
    str=strcat(num2str(i));
    text(graph(i,1),graph(i,2),str);
    hold on;
end
for i=1:obstacle
    w = Rectangle(i,3)-Rectangle(i,1);
    h=Rectangle(i,4)-Rectangle(i,2);
    r = rectangle('Position',[Rectangle(i,1) Rectangle(i,2) w h]);
    hold on;
end

% a=[0,10000,0,10000];
% axis(a);%���������᷶Χ���ݺ��
axis fill

graphw=zeros(vertice,vertice);
for i=1:vertice
    for j=1:vertice
        graphw(i,j)=abs(graph(i,1)-graph(j,1))+abs(graph(i,2)-graph(j,2));
    end
end