// Fill out your copyright notice in the Description page of Project Settings.


#include "AMyActor.h"

// 로그 출력을 위한 커스텀 로그 카테고리 정의
DEFINE_LOG_CATEGORY_STATIC(LogMyActor, Log, All);

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 멤버 변수 초기화
	CurrentPosition = FVector2D(0.0f, 0.0f);
	TotalDistance = 0.0f;
	TotalEventCount = 0;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// 액터가 스폰(생성)되면 Move 함수를 호출하여 시뮬레이션을 시작합니다.
	Move();
}

void AMyActor::Move()
{
    UE_LOG(LogMyActor, Warning, TEXT("====== Start Simulation ====="));

    FVector2D PreviousPosition = CurrentPosition;

    // 시작점 좌표 출력
    UE_LOG(LogMyActor, Warning, TEXT("시작 좌표: (%f, %f)"), CurrentPosition.X, CurrentPosition.Y);

    // 10회 이동을 위한 루프
    for (int32 i = 1; i <= 10; ++i)
    {
        // 이전 위치 저장
        PreviousPosition = CurrentPosition;

        // Step() 함수를 호출하여 다음 좌표 계산
        CurrentPosition.X += Step();
        CurrentPosition.Y += Step();

        // 현재 좌표 출력
        UE_LOG(LogMyActor, Log, TEXT("[스텝 %d] 현재 좌표: (%f, %f)"), i, CurrentPosition.X, CurrentPosition.Y);

        // 이전 좌표로부터의 이동 거리 계산 및 출력
        float StepDistance = CalculateDistance(PreviousPosition, CurrentPosition);
        TotalDistance += StepDistance;
        UE_LOG(LogMyActor, Log, TEXT("  ㄴ 이동 거리: %f"), StepDistance);

        // 50% 확률로 이벤트 발생 여부 확인 및 출력
        if (CreateEvent() == 1)
        {
            TotalEventCount++;
            UE_LOG(LogMyActor, Log, TEXT("  ㄴ 이벤트 발생! (O)"));
        }
        else
        {
            UE_LOG(LogMyActor, Log, TEXT("  ㄴ 이벤트 발생 안함 (X)"));
        }
    }

    UE_LOG(LogMyActor, Warning, TEXT("====== 이동 시뮬레이션 종료 ======"));
    // 최종 결과(총 이동 거리, 총 이벤트 발생 횟수) 출력
    UE_LOG(LogMyActor, Warning, TEXT("총 이동 거리: %f"), TotalDistance);
    UE_LOG(LogMyActor, Warning, TEXT("총 이벤트 발생 횟수: %d회"), TotalEventCount);
}

int32 AMyActor::Step()
{
    // 0 또는 1을 랜덤하게 반환
    return FMath::RandRange(0, 1);
}

float AMyActor::CalculateDistance(const FVector2D& First, const FVector2D& Second)
{
    // FMath::sqrt() 함수를 통해 두 점 사이의 거리를 계산
    float dx = First.X - Second.X;
    float dy = First.Y - Second.Y;
    return FMath::Sqrt(dx * dx + dy * dy);
}

int32 AMyActor::CreateEvent()
{
    // FMath::FRand()는 0.0과 1.0 사이의 랜덤한 실수를 반환
    // 0.5보다 작을 확률은 50%
    return (FMath::FRand() < 0.5f) ? 1 : 0;
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

