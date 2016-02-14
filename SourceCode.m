function SCISVM()
clc;
load('handan1-3.mat');
clusterdata=ClusterData;
means=Means;
orginaldata=handandata1;
 [m,n]=size(clusterdata);
 gap=20;
 result=0;
 for col=1:24
    clusterlabel=zeros(m,1);
    userdata=size(m-gap,gap);
    userlabel=size(m-gap);
    for i=gap:1:m-1
        for j=gap-1:-1:1
            userdata(i-gap+1,gap-j)=clusterdata(i-j,col);
        end
      userlabel(i-gap+1)=clusterdata(i,col);
    end
    predictdata=clusterdata(m-gap:m-1,col);
    predictlabel=clusterdata(m,col);
    model(col)=svmtrain(userlabel',userdata,'-c 1 -g 0.07');
    [predict_label, accuracy] =svmpredict(predictlabel',predictdata',model(col));
    [predict_label,predictlabel,col]
    result=result+accuracy;
    count=1;
    for k=1:1:m-1
        if clusterdata(k,col)==predict_label
            clusterlabel(count)=k;
            count=count+1;
        end
    end
    count=count-1;
    data=size(count,1);
    for k=1:1:count
        label=int32(clusterlabel(k));
        data(k)=orginaldata(label,col);
    end
    [mu,sigma]=normfit(data);
    distance=size(count,1);
    flag=-1;
    sum=0
    for k=1:count
        if data(k)~=mu
        distance(k)=1/abs(data(k)-mu);
        sum=distance(k)+sum;
        else
            flag=k;
        end
    end
    MIU=0;
    if( flag<0)
        for k=1:count
            MIU=MIU+(distance(k)/sum)*data(k);
        end
    else
        flag=int32(flag)
        MIU=data(flag);
    end
    MaxData(col)=max(data);
    MinData(col)=min(data);
    MIUS(col)=MIU;
    %[max(data),min(data),MIU,handandata7(m,col)]
 end
 MaxData
 MinData
 MIUS
 truedata=orginaldata(m,:)
%A=handandata7(m-gap:m,24);
%alpha=0.05;
%[mu,sigma]=normfit(A);
%p1=normcdf(A,mu,sigma);
%[H1,s1]=kstest(A,[A,p1],alpha);
%n=length(A);
%if H1==0
%disp('该数据服从正态分布。')
%end
 result=result/col;
 summae=0;
 sumrmae=0;
 sumtrue=0;
for k=1:24
    summae=summae+(abs(truedata(k)-MIUS(k)));
    sumrmae=sumrmae+(truedata(k)-MIUS(k))*(truedata(k)-MIUS(k));
    sumtrue=sumtrue+truedata(k);
end
summae=(summae/sumtrue)
sumrmae=sqrt(sumrmae)/sumtrue
result
end