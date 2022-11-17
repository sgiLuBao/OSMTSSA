inputfile='input70.txt';
fidpro=fopen(inputfile,'r');
vertice=fscanf(fidpro,'%d',1);      %点数
graph=ones(vertice,2);
particle = ones(1,3*vertice-3);
for i=1:vertice
    graph(i,1)=fscanf(fidpro,'%f',1);%横坐标
    graph(i,2)=fscanf(fidpro,'%f',1);%纵坐标
end
fclose(fidpro);
inputfile='result.txt';
fidpro=fopen(inputfile,'r');
for i=1:3*(vertice-1)
    particle(1,i)=fscanf(fidpro,'%d',1);
end
gbfitness = fscanf(fidpro, '%f',1);
totaleval = fscanf(fidpro, '%d',1);
eval = zeros(totaleval,1);
evalgbest = zeros(totaleval,1);
for i = 1:totaleval
    eval(i) = fscanf(fidpro,'%d',1);
    evalgbest(i) = fscanf(fidpro, '%f',1);
end
fclose(fidpro);
figure(1);
plot(eval,evalgbest,'r-');
figure(2);
for i=1:vertice
    str = num2str(i);
    plot(graph(i,1),graph(i,2),'r.');
    hold on;
end
for i=1:(vertice-1)
    x1 = graph(particle(1,i*3-2),1);
    y1 = graph(particle(1,i*3-2),2);
    x2 = graph(particle(1,i*3-1),1);
    y2 = graph(particle(1,i*3-1),2);
    fx = abs(x1-x2);
    fy = abs(y1-y2);
    if particle(1,i*3) ==0 || particle(1,i*3) ==1
        if fx > fy
            if particle(1,i*3) == 0
                sy = y1;
                if x1<x2
                    if y1<y2
                        sx = x2-y2+y1;
                    else 
                        sx = x2-y1+y2;
                    end
                else
                    if y1<y2
                        sx = x2-y1+y2;
                    else
                        sx = x2-y2+y1;
                    end
                end
            else
                sy = y2;
                if x1<x2
                    if y1>y2
                        sx = x1+y1-y2;
                    else
                        sx = x1+y2-y1;
                    end
                else
                    if y1<y2
                        sx = x1+y1-y2;
                    else
                        sx = x1+y2-y1;
                    end
                end
            end
        else
            if particle(1,i*3) == 0
                sx = x1;
                if x1<x2
                    if y1>y2
                        sy = y2+x2-x1;
                    else
                        sy = y2-x2+x1;
                    end
                else
                    if y1<y2
                        sy = y2+x2-x1;
                    else
                        sy = y2-x2+x1;
                    end
                end
            else
                sx = x2;
                if x1 < x2
                    if y1>y2
                        sy = y1-x2+x1;
                    else
                        sy = y1+x2-x1;
                    end
                else
                    if y1>y2
                        sy = y1+x2-x1;
                    else
                        sy = y1-x2+x1;
                    end
                end
            end
        end
    end
    if particle(1,i*3) ==2 || particle(1,i*3) ==3
        if particle(1,i*3) == 2
            sx = graph(particle(1,i*3-2),1);
            sy = graph(particle(1,i*3-1),2);
        else
            sx = graph(particle(1,i*3-1),1);
            sy = graph(particle(1,i*3-2),2);
        end
    end
    plot([x1,sx],[y1,sy]);
    hold on;
    plot([sx,x2],[sy,y2]);
end
hold off;