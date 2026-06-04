// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename T>
class TObservable
{
public:

	using FCallback = TFunction<void(const T&)>;

	/** Subscribe to notifications. Returns a handle used to unsubscribe. */
	int32 Subscribe(FCallback Callback)
	{
		int32 handle = NextHandle++;
		Subscribers.Add(Handle, MoveTemp(Callback));
		return Handle;
	}

	/** Unsubscribe using the handle returned by Subscribe. Safe to call with invalid handles. */
	void Unsubscribe(int32 Handle)
	{
		Subscribers.Remove(Handle);
	}

	/** Notify all current subscribers with the given value. */
	void Notify(const T& Value)
	{
		for (auto& Pair : Subscribers)
			if (Pair.Value)
				Pair.Value(Value);
	}

	/** Returns true if at least one subscriber is registered. */
    bool HasSubscribers() const
    {
        return Subscribers.Num() > 0;
    }

    /** Remove all subscribers at once. */
    void Clear()
    {
        Subscribers.Empty();
    }

private:
	TMap<int32, FCallback> Subscribers;
	int32 NextHandle;

};
